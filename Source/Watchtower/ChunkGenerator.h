// Copyright 2017 William Yates

#pragma once

#include "Chunk.h"

struct FBlockFace
{
	bool bCulled;
	uint8 Type;
	uint8 Side;

	FBlockFace()
	{
		bCulled = false;
		Type = 0;
		Side = 0;
	}

	FORCEINLINE bool Equals(const FBlockFace& Face) const
	{
		return Face.bCulled == bCulled && Face.Type == Type;
	}
};

class WATCHTOWER_API FChunkGenerator
{
private:
	AChunk* Chunk;
	URuntimeMeshComponent* Mesh;

private:
	static const uint32 Scale = FBlock::SIZE;

	FBlockFace GetBlockFace(const FIntVector& InCoordinate, uint8 Side) const;

public:
	void Generate();

	FChunkGenerator(AChunk* Target, URuntimeMeshComponent* TargetMesh);
	~FChunkGenerator();
};
