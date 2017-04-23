// Copyright 2016 William Yates

#pragma once

#include "Chunk.h"

#include "Object.h"
#include "VoxelMapData.generated.h"

UCLASS()
class WATCHTOWER_API UVoxelMapData : public UObject
{
	GENERATED_BODY()

private:
	TArray<Chunk> chunks;

	uint32 width;
	uint32 height;
	uint32 depth;

public:
	void Save(const FString& fileName);
	void Load(const FString& fileName);

	Chunk& GetChunk(int x, int y, int z);

	UVoxelMapData();
	~UVoxelMapData();
};
