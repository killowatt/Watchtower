// Copyright 2017 William Yates

#include "Watchtower.h"
#include "VoxelMapData.h"

FBlock::FBlock()
{
	Active = false;
	Color = FColor::White;
}
FBlock FBlock::Default = FBlock();

FBlock& UVoxelMapData::GetBlock(int32 X, int32 Y, int32 Z)
{
	if (X >= Size.X || Y >= Size.Y || Z >= Size.Z ||
		X < 0 || Y < 0 || Z < 0)
	{
		return FBlock::Default;
	}
	return Blocks[GetBlockIndex(X, Y, Z)];
}
FBlock& UVoxelMapData::GetBlock(const FIntVector& Coordinates)
{
	return GetBlock(Coordinates.X, Coordinates.Y, Coordinates.Z);
}
FORCEINLINE uint32 UVoxelMapData::GetBlockIndex(int32 X, int32 Y, int32 Z) const
{
	return X + Y * Size.X + Z * Size.X * Size.Y;
}

FORCEINLINE const FIntVector& UVoxelMapData::GetSize() const
{
	return Size;
}

void UVoxelMapData::Save(const FString& FileName)
{
	TArray<uint8> Buffer;
	FMemoryWriter Writer(Buffer);

	Writer << Name; // Write the name of the map to the file.
	Writer << Size; // Write the size of the map to the file.

}
void UVoxelMapData::Load(const FString& FileName)
{
	// Layla's
	TArray<uint8> CompressedData;
	if (!FFileHelper::LoadFileToArray(CompressedData, *(FPaths::GameContentDir() + FileName + ".map")))
	{
		return;
	}

	FMemoryReader MemoryReader(CompressedData, true);

	TArray<uint8> BlockData;

	MemoryReader << Size;
	Size = FIntVector(Size.X, Size.Z, Size.Y);

	Blocks.SetNum(Size.X * Size.Y * Size.Z);
	BlockData.SetNum(Size.X * Size.Y * Size.Z);

	MemoryReader.Serialize(BlockData.GetData(), BlockData.Num());

	for (int32 x = 0; x < BlockData.Num(); x++)
	{
		Blocks[x].Active = BlockData[x] > 0;
	}
}

UVoxelMapData::UVoxelMapData()
{
}
UVoxelMapData::~UVoxelMapData()
{
}
