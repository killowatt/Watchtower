// Copyright 2017 William Yates

#include "Watchtower.h"
#include "VoxelMapData.h"

FBlock& FChunk::GetBlock(int32 X, int32 Y, int32 Z)
{
	if (X >= WIDTH || Y >= DEPTH || Z >= HEIGHT ||
		X < 0 || Y < 0 || Z < 0)
	{
		return FBlock::Default;
	}
	return Blocks[X + Y * WIDTH + Z * WIDTH * DEPTH];
}
FBlock& FChunk::GetBlock(const FIntVector& Coordinates)
{
	return GetBlock(Coordinates.X, Coordinates.Y, Coordinates.Z);
}

FBlock::FBlock()
{
	Active = false;
	Color = FColor::White;
}
FBlock FBlock::Default = FBlock();

FChunk::FChunk()
{
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
	//// Layla's
	//TArray<uint8> CompressedData;
	//if (!FFileHelper::LoadFileToArray(CompressedData, *(FPaths::GameContentDir() + FileName + ".map")))
	//{
	//	return;
	//}

	//FMemoryReader MemoryReader(CompressedData, true);

	//MemoryReader << Size;
	//Size = FIntVector(Size.X, Size.Z, Size.Y);
	////Blocks.SetNum(Size.X * Size.Y * Size.Z);
	//MemoryReader.Serialize(Blocks.GetData(), Blocks.Num());
}

UVoxelMapData::UVoxelMapData()
{
	//Name = FName(TEXT("DefaultMap"));
}

UVoxelMapData::~UVoxelMapData()
{
}
