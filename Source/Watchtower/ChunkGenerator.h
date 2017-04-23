// Copyright 2016 William Yates

#pragma once

#include "Chunk.h"

/**
*
*/
class WATCHTOWER_API ChunkGenerator
{
private:
	bool xPositive;
	bool xNegative;
	bool yPositive;
	bool yNegative;
	bool zPositive;
	bool zNegative;
	Chunk* chunk;
	URuntimeMeshComponent* mesh;

	TArray<FVector> vertices;
	TArray<FVector> normals;
	TArray<FRuntimeMeshTangent> tangents;
	TArray<FColor> colors;
	TArray<FVector2D> textureCoordinates;
	TArray<int32> triangles;

private:
	inline void UpdateActiveFaces(int x, int y, int z);
	inline void AppendVertex(float x, float y, float z, FVector offset);
	inline void AppendNormal(FVector normal);
	inline void AppendColor(FColor color);
	inline void AppendTriangles();
	inline void GenerateBlockData(FVector position, FColor color);

public:
	void Generate();

	ChunkGenerator(Chunk* targetChunk, URuntimeMeshComponent* targetMesh);
	~ChunkGenerator();
};
