// Copyright 2016 William Yates

#include "Watchtower.h"
#include "ChunkGenerator.h"

inline void ChunkGenerator::UpdateActiveFaces(int x, int y, int z)
{
	xPositive = true;
	if (x < Chunk::WIDTH - 1)
		xPositive = !chunk->GetBlock(x + 1, y, z).Active;

	xNegative = true;
	if (x > 0)
		xNegative = !chunk->GetBlock(x - 1, y, z).Active;

	yPositive = true;
	if (y < Chunk::DEPTH - 1)
		yPositive = !chunk->GetBlock(x, y + 1, z).Active;

	yNegative = true;
	if (y > 0)
		yNegative = !chunk->GetBlock(x, y - 1, z).Active;

	zPositive = true;
	if (z < Chunk::HEIGHT - 1)
		zPositive = !chunk->GetBlock(x, y, z + 1).Active;

	zNegative = true;
	if (z > 0)
		zNegative = !chunk->GetBlock(x, y, z - 1).Active;
}

inline void ChunkGenerator::AppendVertex(float x, float y, float z, FVector offset)
{
	vertices.Add(FVector(x, y, z) + offset);
}
inline void ChunkGenerator::AppendNormal(FVector normal)
{
	normals.Add(normal);
	normals.Add(normal);
	normals.Add(normal);
	normals.Add(normal);
}
inline void ChunkGenerator::AppendColor(FColor color)
{
	colors.Add(color);
	colors.Add(color);
	colors.Add(color);
	colors.Add(color);
}
inline void ChunkGenerator::AppendTriangles()
{
	int32 count = vertices.Num();

	triangles.Add(count - 1);
	triangles.Add(count - 2);
	triangles.Add(count - 4);
	triangles.Add(count - 2);
	triangles.Add(count - 3);
	triangles.Add(count - 4);

	// Flipped Face Mode
	//triangles.Add(count - 4);
	//triangles.Add(count - 3);
	//triangles.Add(count - 2);
	//triangles.Add(count - 4);
	//triangles.Add(count - 2);
	//triangles.Add(count - 1);
}

void ChunkGenerator::GenerateBlockData(FVector position, FColor color)
{
	if (xPositive)
	{
		AppendVertex(0.5f, -0.5f, -0.5f, position); // We need 24 verts otherwise normals would be incorrect.
		AppendVertex(0.5f, 0.5f, -0.5f, position);
		AppendVertex(0.5f, 0.5f, 0.5f, position);
		AppendVertex(0.5f, -0.5f, 0.5f, position);

		AppendColor(color);
		AppendNormal(FVector(1, 0, 0));
		AppendTriangles();
	}
	if (xNegative)
	{
		AppendVertex(-0.5f, -0.5f, -0.5f, position);
		AppendVertex(-0.5f, -0.5f, 0.5f, position);
		AppendVertex(-0.5f, 0.5f, 0.5f, position);
		AppendVertex(-0.5f, 0.5f, -0.5f, position);

		AppendColor(color);
		AppendNormal(FVector(-1, 0, 0));
		AppendTriangles();
	}
	if (yPositive)
	{
		AppendVertex(-0.5f, 0.5f, -0.5f, position);
		AppendVertex(-0.5f, 0.5f, 0.5f, position);
		AppendVertex(0.5f, 0.5f, 0.5f, position);
		AppendVertex(0.5f, 0.5f, -0.5f, position);

		AppendColor(color);
		AppendNormal(FVector(0, 1, 0));
		AppendTriangles();
	}
	if (yNegative)
	{
		AppendVertex(-0.5f, -0.5f, -0.5f, position);
		AppendVertex(0.5f, -0.5f, -0.5f, position);
		AppendVertex(0.5f, -0.5f, 0.5f, position);
		AppendVertex(-0.5f, -0.5f, 0.5f, position);

		AppendColor(color);
		AppendNormal(FVector(0, -1, 0));
		AppendTriangles();
	}
	if (zPositive)
	{
		AppendVertex(-0.5f, -0.5f, 0.5f, position);
		AppendVertex(0.5f, -0.5f, 0.5f, position);
		AppendVertex(0.5f, 0.5f, 0.5f, position);
		AppendVertex(-0.5f, 0.5f, 0.5f, position);

		AppendColor(color);
		AppendNormal(FVector(0, 0, 1));
		AppendTriangles();
	}
	if (zNegative)
	{
		AppendVertex(-0.5f, -0.5f, -0.5f, position);
		AppendVertex(-0.5f, 0.5f, -0.5f, position);
		AppendVertex(0.5f, 0.5f, -0.5f, position);
		AppendVertex(0.5f, -0.5f, -0.5f, position);

		AppendColor(color);
		AppendNormal(FVector(0, 0, -1));
		AppendTriangles();
	}
}

void ChunkGenerator::Generate()
{
	int vertexArraySize = 0;
	int triangleArraySize = 0;

	// Calculate the reserve size for the arrays.
	for (int x = 0; x < Chunk::WIDTH; x++)
	{
		for (int y = 0; y < Chunk::DEPTH; y++)
		{
			for (int z = 0; z < Chunk::HEIGHT; z++)
			{
				if (!chunk->GetBlock(x, y, z).Active)
					continue;

				UpdateActiveFaces(x, y, z);
				int sides = xPositive + xNegative + yPositive + yNegative + zPositive + zNegative;
				vertexArraySize += sides * 4;
				triangleArraySize += sides * 6;
			}
		}
	}

	// Disregard completely empty chunks
	if (vertexArraySize <= 0 || triangleArraySize <= 0)
		return;

	vertices.Reserve(vertexArraySize);
	colors.Reserve(vertexArraySize);
	normals.Reserve(vertexArraySize);
	triangles.Reserve(triangleArraySize);

	// Create the vertex data
	for (int x = 0; x < Chunk::WIDTH; x++)
	{
		for (int y = 0; y < Chunk::DEPTH; y++)
		{
			for (int z = 0; z < Chunk::HEIGHT; z++)
			{
				if (!chunk->GetBlock(x, y, z).Active)
					continue;

				UpdateActiveFaces(x, y, z);
				GenerateBlockData(FVector(x, y, z), chunk->GetBlock(x, y, z).Color);
			}
		}
	}

	mesh->CreateMeshSection(0, vertices, triangles, normals, textureCoordinates, colors,
		tangents);
}

ChunkGenerator::ChunkGenerator(Chunk* targetChunk, URuntimeMeshComponent* targetMesh)
{
	chunk = targetChunk;
	mesh = targetMesh;
}
ChunkGenerator::~ChunkGenerator()
{
}
