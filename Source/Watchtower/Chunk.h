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

	UVoxelMapData* MapData;
	FIntVector MapCoordinates;
	FIntVector VolumeSize;
	URuntimeMeshComponent* RuntimeMesh;

	UMaterial* Material;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void OnConstruction(const FTransform& Transform) override;

public:
	FBlock& GetBlockLocal(const FIntVector& Coordinates);
	FBlock& GetBlockLocal(int32 X, int32 Y, int32 Z);

	const FIntVector& GetVolumeSize() const;

	void SetRelativeMapData(UVoxelMapData* MapData, 
		const FIntVector& Coordinates, const FIntVector& VolumeSize);
	void Generate();
	
	// Sets default values for this actor's properties
	AChunk();
};
