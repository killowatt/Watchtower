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
	bool xPositive;
	bool xNegative;
	bool yPositive;
	bool yNegative;
	bool zPositive;
	bool zNegative;
	FChunk* Chunk;
	URuntimeMeshComponent* Mesh;

	TArray<FVector> Vertices;
	TArray<FVector> Normals;
	TArray<FRuntimeMeshTangent> Tangents;
	TArray<FColor> Colors;
	TArray<FVector2D> TextureCoordinates;
	TArray<int32> Triangles;

private:
	static const uint32 Scale = FBlock::SIZE;

	inline void UpdateActiveFaces(uint32 x, uint32 y, uint32 z);
	inline void AppendVertex(float x, float y, float z, FVector Offset);
	inline void AppendNormal(FVector Normal);
	inline void AppendColor(FColor Color);
	inline void AppendTriangles();
	inline void GenerateBlockData(FVector Position, FColor Color);


	FIntVector dims;

	bool f(uint32 i, uint32 j, uint32 k) {
		return Chunk->Blocks[i + dims[0] * (j + dims[1] * k)].Active;
	};



	FBlockFace GetBlockFace(const FIntVector& InCoordinate, uint8 Side) const;

public:
	void Generate();

	FChunkGenerator(FChunk* TargetChunk, URuntimeMeshComponent* TargetMesh);
	~FChunkGenerator();
};
