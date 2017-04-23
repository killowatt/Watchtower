// Copyright 2016 William Yates

#include "Watchtower.h"
#include "Chunk.h"
#include "ChunkGenerator.h"

FBlock::FBlock(bool active, FColor color)
{
	Active = active;
	Color = color;
}

FBlock& Chunk::GetBlock(int x, int y, int z)
{
	return blocks[x + WIDTH * (z + HEIGHT * y)];
}
void Chunk::SetBlock(int x, int y, int z, FBlock block)
{
	blocks[x + WIDTH * (z + HEIGHT * y)] = block;
}

void Chunk::Generate()
{
	for (int x = 0; x < 16; x++)
	{
		for (int y = 0; y < 16; y++)
		{
			GetBlock(x, y, 0).Active = true;
			GetBlock(x, y, 0).Color = FColor::Blue;
		}
	}

	GetBlock(4, 4, 1).Active = true;
	GetBlock(4, 4, 1).Color = FColor::Red;
	GetBlock(12, 12, 1).Active = true;
	GetBlock(12, 12, 1).Color = FColor::Green;

	ChunkGenerator generator(this, RuntimeMesh);
	generator.Generate();
}

Chunk::Chunk()
{
}

Chunk::~Chunk()
{
}
