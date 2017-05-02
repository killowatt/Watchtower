// Copyright 2017 William Yates

#pragma once

#include "Core.h"
#include "VoxelMapData.generated.h"

USTRUCT()
struct FBlock
{
	GENERATED_BODY()

	UPROPERTY()
	bool Active;

	UPROPERTY()
	FColor Color;

	static const uint32 Size = 100;
	static FBlock Default;

	FBlock();
};

UCLASS()
class WATCHTOWER_API UVoxelMapData : public UObject
{
	GENERATED_BODY()

private:
	TArray<FBlock> Blocks;

public:
	TArray<class AChunk*> Chunks;
private:

	FIntVector Size;

	const static int32 ChunkWidth = 16; // This merely defines how big most sections should be.
	const static int32 ChunkDepth = 16; // Chunks can be equal to or smaller than this size.

	FName Name;

public:
	FBlock& GetBlock(int32 X, int32 Y, int32 Z);
	FBlock& GetBlock(const FIntVector& Coordinates);
	uint32 GetBlockIndex(int32 X, int32 Y, int32 Z) const;

	FBlock& GetAdjacentBlock(const FIntVector& Coordinates, const FIntVector& Side);

	
	const FIntVector& GetSize() const;

	bool Callback(FIntVector Copy, FIntVector Face, FVector Direction, FBlock Block);
	void TryRaycastModify(FVector Direction, FVector Position, float Radius, FBlock Block);

	void Save(const FString& FileName);
	void Load(const FString& FileName);

	UVoxelMapData();
	~UVoxelMapData();
};
