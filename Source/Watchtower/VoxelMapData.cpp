// Copyright 2016 William Yates

#include "Watchtower.h"
#include "VoxelMapData.h"

void UVoxelMapData::Save(const FString& fileName)
{
	// FMemoryReader

	// https://wiki.unrealengine.com/Save_System,_Read_%26_Write_Any_Data_to_Compressed_Binary_Files
	// https://gist.github.com/aylaylay/88941a6aa31eccf1327a101b79d71831
	// FMemoryWriter

	FArchive v;

	//for (int i = 0; i < width * height; i++)
	//{
	//	//buffer << chunks[i].
	//}
	
}

Chunk& UVoxelMapData::GetChunk(int x, int y, int z)
{
	return chunks[x + width * (z + height * y)];
}

UVoxelMapData::UVoxelMapData()
{
}

UVoxelMapData::~UVoxelMapData()
{
}
