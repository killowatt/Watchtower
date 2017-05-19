// Copyright 2017 William Yates

#include "Watchtower.h"
#include "Chunk.h"
#include "ChunkGenerator.h"

FBlock& AChunk::GetBlockLocal(const FIntVector& Coordinates)
{
	return MapData->GetBlock(MapCoordinates + Coordinates);
}
FBlock& AChunk::GetBlockLocal(int32 X, int32 Y, int32 Z)
{
	return GetBlockLocal(FIntVector(X, Y, Z));
}

const FIntVector& AChunk::GetVolumeSize() const
{
	return VolumeSize;
}

void AChunk::SetRelativeMapData(UVoxelMapData* MapData,
	const FIntVector& MapCoordinates, const FIntVector& VolumeSize)
{
	this->MapData = MapData;
	this->MapCoordinates = MapCoordinates;
	this->VolumeSize = VolumeSize;
}
void AChunk::Generate()
{
	FChunkGenerator Generator(this, RuntimeMesh);
	Generator.Generate();
}

void AChunk::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime); // Call parent class tick function  

	if (PleaseUpdate)
	{
		if (GEngine->GetNetMode(GetWorld()) == NM_DedicatedServer)
		{
			Generate(); // do simple collision instead of genning a collision from mesh
			PleaseUpdate = false;
		}
		else if (GEngine->GetNetMode(GetWorld()) == NM_Client)
		{
			Generate();
			PleaseUpdate = false;
		}
		else
		{
			UE_LOG(WTVoxel, Error, TEXT("Unknown end-user type in chunk update."));
			PleaseUpdate = false;
		}
	}
}


// Sets default values
AChunk::AChunk()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RuntimeMesh = CreateDefaultSubobject<URuntimeMeshComponent>(TEXT("Runtime Mesh"));
	RootComponent = RuntimeMesh;

	static ConstructorHelpers::FObjectFinder<UMaterial> Material(TEXT("/Game/ChunkMaterial"));
	if (Material.Object)
	{
		RuntimeMesh->SetMaterial(0, (UMaterial*)Material.Object);
	}

	PleaseUpdate = false;
}

// Called when the game starts or when spawned
void AChunk::BeginPlay()
{
	Super::BeginPlay();

	RuntimeMesh->SetCollisionResponseToChannel(COLLISION_VOXELPLAYER, ECR_Block);
	//RuntimeMesh->SetCollisionResponseToChannel(COLLISION_VOXEL, ECR_Block);
}
void AChunk::OnConstruction(const FTransform& Transform)
{
}
