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

// Sets default values
AChunk::AChunk()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	RuntimeMesh = CreateDefaultSubobject<URuntimeMeshComponent>(TEXT("Runtime Mesh"));
	RootComponent = RuntimeMesh;

	static ConstructorHelpers::FObjectFinder<UMaterial> Material(TEXT("/Game/ChunkMaterial"));
	if (Material.Object)
	{
		RuntimeMesh->SetMaterial(0, (UMaterial*)Material.Object);
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("got material"));
	}
}

// Called when the game starts or when spawned
void AChunk::BeginPlay()
{
	Super::BeginPlay();
}
void AChunk::OnConstruction(const FTransform& Transform)
{


	// TEmp
	//ChunkData = new FChunk();



	//TArray<FVector> Vertices;
	//TArray<FVector> Normals;
	//TArray<FRuntimeMeshTangent> Tangents;
	//TArray<FVector2D> TextureCoordinates;
	//TArray<int32> Triangles;

	//URuntimeMeshLibrary::CreateBoxMesh(FVector(100, 100, 100), Vertices, Triangles, Normals, TextureCoordinates, Tangents);



	//// Create the mesh section specifying collision
	//RuntimeMesh->CreateMeshSection(0, Vertices, Triangles, Normals, TextureCoordinates, TArray<FColor>(), Tangents, true, EUpdateFrequency::Infrequent);
}
