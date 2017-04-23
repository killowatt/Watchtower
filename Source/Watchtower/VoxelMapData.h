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

UCLASS()
class WATCHTOWER_API UVoxelMapData : public UObject
{
	GENERATED_BODY()

private:
	TArray<FBlock> Blocks;
	FIntVector Size;

	FName Name;

public:
	FBlock& GetBlock(int32 X, int32 Y, int32 Z);
	FBlock& GetBlock(const FIntVector& Coordinates);
	uint32 GetBlockIndex(int32 X, int32 Y, int32 Z) const;

	const FIntVector& GetSize() const;

	void Save(const FString& FileName);
	void Load(const FString& FileName);

	UVoxelMapData();
	~UVoxelMapData();
};
