// Copyright 2017 William Yates

#pragma once

#include "Core.h"
#include "VoxelMapData.generated.h"

USTRUCT()
struct FBlock
{
	GENERATED_BODY()

	bool Active;
	FColor Color;

	static const uint32 SIZE = 100;
	static FBlock Default;

	FBlock();
};
struct FChunk
{
	static const int WIDTH = 16;
	static const int DEPTH = 16;
	static const int HEIGHT = 128;
	
	FBlock& GetBlock(int32 X, int32 Y, int32 Z);
	FBlock& GetBlock(const FIntVector& Coordinate);

	FBlock Blocks[WIDTH * HEIGHT * DEPTH];

	FChunk();
};

UCLASS()
class WATCHTOWER_API UVoxelMapData : public UObject
{
	GENERATED_BODY()

private:
	TArray<FChunk> Chunks;
	FIntVector Size;

	FName Name;

public:
	FChunk& GetChunk(const FIntRect& Coordinates);

	void Save(const FString& FileName);
	void Load(const FString& FileName);

	UVoxelMapData();
	~UVoxelMapData();
};
