// Copyright 2016 William Yates

#pragma once

#include "Core.h"
#include "RuntimeMeshComponent.h"

#include "Chunk.generated.h"

USTRUCT()
struct FBlock
{
	GENERATED_BODY()

	bool Active;
	FColor Color;

	static const uint32 SIZE = 100;

	FBlock(bool active = false, FColor color = FColor());
};

class WATCHTOWER_API Chunk
{
public:
	static const int WIDTH = 16;
	static const int HEIGHT = 16;
	static const int DEPTH = 16;

private:
	FBlock blocks[WIDTH * HEIGHT * DEPTH];
	URuntimeMeshComponent* RuntimeMesh;

public:
	FBlock& GetBlock(int x, int y, int z);
	void SetBlock(int x, int y, int z, FBlock block);

	void Generate();

	Chunk();
	~Chunk();
};
