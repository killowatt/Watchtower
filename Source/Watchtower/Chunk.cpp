// Copyright 2017 William Yates

#include "Watchtower.h"
#include "Chunk.h"
#include "ChunkGenerator.h"

void AChunk::Generate()
{
	FColor col = FColor::MakeRandomColor();

	uint32 r = FMath::RandRange(1, 15);
	//r = 64;
	for (int x = 0; x < 16; x++)
	{
		for (int y = 0; y < 16; y++)
		{
			for (uint32 z = 0; z < r; z++)
			{
				ChunkData->GetBlock(x, y, z).Active = true;
				ChunkData->GetBlock(x, y, z).Color = col;
			}
		}
	}

	ChunkData->GetBlock(4, 4, r).Active = true;
	ChunkData->GetBlock(4, 4, r).Color = FColor::Red;
	ChunkData->GetBlock(12, 12, r).Active = true;
	ChunkData->GetBlock(12, 12, r).Color = FColor::Green;

	FChunkGenerator Generator(ChunkData, RuntimeMesh);
	Generator.Generate();

	//SetActorScale3D(FVector(100, 100, 100));
}

// Sets default values
AChunk::AChunk()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	RuntimeMesh = CreateDefaultSubobject<URuntimeMeshComponent>(TEXT("Runtime Mesh"));
	RootComponent = RuntimeMesh;

	static ConstructorHelpers::FObjectFinder<UMaterial> Material(TEXT("/Game/ChunkMaterial"));

	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("fail if no procede msg"));
	if (Material.Object != NULL)
	{
		material = (UMaterial*)Material.Object;
		RuntimeMesh->SetMaterial(0, material);
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
	ChunkData = new FChunk();
	Generate();



	//TArray<FVector> Vertices;
	//TArray<FVector> Normals;
	//TArray<FRuntimeMeshTangent> Tangents;
	//TArray<FVector2D> TextureCoordinates;
	//TArray<int32> Triangles;

	//URuntimeMeshLibrary::CreateBoxMesh(FVector(100, 100, 100), Vertices, Triangles, Normals, TextureCoordinates, Tangents);



	//// Create the mesh section specifying collision
	//RuntimeMesh->CreateMeshSection(0, Vertices, Triangles, Normals, TextureCoordinates, TArray<FColor>(), Tangents, true, EUpdateFrequency::Infrequent);
}
