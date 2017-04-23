// Copyright 2017 William Yates

#pragma once

#include "GameFramework/Actor.h"
#include "RuntimeMeshComponent.h"
#include "VoxelMapData.h"
#include "Chunk.generated.h"

UCLASS()
class WATCHTOWER_API AChunk : public AActor
{
	GENERATED_BODY()

	FChunk* ChunkData;
	URuntimeMeshComponent* RuntimeMesh;

	UMaterial* material;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void OnConstruction(const FTransform& Transform) override;

public:	

	void Generate();
	
	// Sets default values for this actor's properties
	AChunk();
};
