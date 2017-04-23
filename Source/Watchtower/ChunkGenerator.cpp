// Copyright 2017 William Yates

#include "Watchtower.h"
#include "ChunkGenerator.h"

inline void FChunkGenerator::UpdateActiveFaces(uint32 x, uint32 y, uint32 z)
{
	xPositive = true;
	if (x < FChunk::WIDTH - 1)
		xPositive = !Chunk->GetBlock(x + 1, y, z).Active;

	xNegative = true;
	if (x > 0)
		xNegative = !Chunk->GetBlock(x - 1, y, z).Active;

	yPositive = true;
	if (y < FChunk::DEPTH - 1)
		yPositive = !Chunk->GetBlock(x, y + 1, z).Active;

	yNegative = true;
	if (y > 0)
		yNegative = !Chunk->GetBlock(x, y - 1, z).Active;

	zPositive = true;
	if (z < FChunk::HEIGHT - 1)
		zPositive = !Chunk->GetBlock(x, y, z + 1).Active;

	zNegative = true;
	if (z > 0)
		zNegative = !Chunk->GetBlock(x, y, z - 1).Active;
}

inline void FChunkGenerator::AppendVertex(float x, float y, float z, FVector Offset)
{
	Vertices.Add(FVector(x * Scale, y * Scale, z * Scale) + Offset * Scale);
}
inline void FChunkGenerator::AppendNormal(FVector Normal)
{
	Normals.Add(Normal);
	Normals.Add(Normal);
	Normals.Add(Normal);
	Normals.Add(Normal);
}
inline void FChunkGenerator::AppendColor(FColor Color)
{
	Colors.Add(Color);
	Colors.Add(Color);
	Colors.Add(Color);
	Colors.Add(Color);
}
inline void FChunkGenerator::AppendTriangles()
{
	int32 Count = Vertices.Num();

	Triangles.Add(Count - 1);
	Triangles.Add(Count - 2);
	Triangles.Add(Count - 4);
	Triangles.Add(Count - 2);
	Triangles.Add(Count - 3);
	Triangles.Add(Count - 4);

	// Flipped Face Mode
	//triangles.Add(count - 4);
	//triangles.Add(count - 3);
	//triangles.Add(count - 2);
	//triangles.Add(count - 4);
	//triangles.Add(count - 2);
	//triangles.Add(count - 1);
}

void FChunkGenerator::GenerateBlockData(FVector Position, FColor Color)
{
	if (xPositive)
	{
		AppendVertex(0.5f, -0.5f, -0.5f, Position); // We need 24 verts otherwise normals would be incorrect.
		AppendVertex(0.5f, 0.5f, -0.5f, Position);
		AppendVertex(0.5f, 0.5f, 0.5f, Position);
		AppendVertex(0.5f, -0.5f, 0.5f, Position);

		AppendColor(Color);
		AppendNormal(FVector(1, 0, 0));
		AppendTriangles();
	}
	if (xNegative)
	{
		AppendVertex(-0.5f, -0.5f, -0.5f, Position);
		AppendVertex(-0.5f, -0.5f, 0.5f, Position);
		AppendVertex(-0.5f, 0.5f, 0.5f, Position);
		AppendVertex(-0.5f, 0.5f, -0.5f, Position);

		AppendColor(Color);
		AppendNormal(FVector(-1, 0, 0));
		AppendTriangles();
	}
	if (yPositive)
	{
		AppendVertex(-0.5f, 0.5f, -0.5f, Position);
		AppendVertex(-0.5f, 0.5f, 0.5f, Position);
		AppendVertex(0.5f, 0.5f, 0.5f, Position);
		AppendVertex(0.5f, 0.5f, -0.5f, Position);

		AppendColor(Color);
		AppendNormal(FVector(0, 1, 0));
		AppendTriangles();
	}
	if (yNegative)
	{
		AppendVertex(-0.5f, -0.5f, -0.5f, Position);
		AppendVertex(0.5f, -0.5f, -0.5f, Position);
		AppendVertex(0.5f, -0.5f, 0.5f, Position);
		AppendVertex(-0.5f, -0.5f, 0.5f, Position);

		AppendColor(Color);
		AppendNormal(FVector(0, -1, 0));
		AppendTriangles();
	}
	if (zPositive)
	{
		AppendVertex(-0.5f, -0.5f, 0.5f, Position);
		AppendVertex(0.5f, -0.5f, 0.5f, Position);
		AppendVertex(0.5f, 0.5f, 0.5f, Position);
		AppendVertex(-0.5f, 0.5f, 0.5f, Position);

		AppendColor(Color);
		AppendNormal(FVector(0, 0, 1));
		AppendTriangles();
	}
	if (zNegative)
	{
		AppendVertex(-0.5f, -0.5f, -0.5f, Position);
		AppendVertex(-0.5f, 0.5f, -0.5f, Position);
		AppendVertex(0.5f, 0.5f, -0.5f, Position);
		AppendVertex(0.5f, -0.5f, -0.5f, Position);

		AppendColor(Color);
		AppendNormal(FVector(0, 0, -1));
		AppendTriangles();
	}
}

//void FChunkGenerator::Generate()
//{
//	uint32 VertexArraySize = 0;
//	uint32 TriangleArraySize = 0;
//
//	// Calculate the reserve size for the arrays.
//	for (int x = 0; x < FChunk::WIDTH; x++)
//	{
//		for (int y = 0; y < FChunk::DEPTH; y++)
//		{
//			for (int z = 0; z < FChunk::HEIGHT; z++)
//			{
//				if (!Chunk->GetBlock(x, y, z).Active)
//					continue;
//
//				UpdateActiveFaces(x, y, z);
//				int sides = xPositive + xNegative + yPositive + yNegative + zPositive + zNegative;
//				VertexArraySize += sides * 4;
//				TriangleArraySize += sides * 6;
//			}
//		}
//	}
//
//	// Disregard completely empty chunks
//	if (VertexArraySize <= 0 || TriangleArraySize <= 0)
//		return;
//
//	Vertices.Reserve(VertexArraySize);
//	Colors.Reserve(VertexArraySize);
//	Normals.Reserve(VertexArraySize);
//	Triangles.Reserve(TriangleArraySize);
//
//	// Create the vertex data
//	for (int x = 0; x < FChunk::WIDTH; x++)
//	{
//		for (int y = 0; y < FChunk::DEPTH; y++)
//		{
//			for (int z = 0; z < FChunk::HEIGHT; z++)
//			{
//				if (!Chunk->GetBlock(x, y, z).Active)
//					continue;
//
//				UpdateActiveFaces(x, y, z);
//				GenerateBlockData(FVector(x, y, z), Chunk->GetBlock(x, y, z).Color);
//			}
//		}
//	}
//
//	Mesh->CreateMeshSection(0, Vertices, Triangles, Normals, TextureCoordinates, Colors,
//		Tangents);
//}

struct FMeshData
{
	TArray<FVector> Vertices;
	TArray<int32> Triangles;
	TArray<FVector> Normals;
	TArray<FVector2D> UV0;
	TArray<FColor> VertexColors;
	TArray<struct FRuntimeMeshTangent> Tangents;
};
static const FVector VertexOffsets[24] =
{
	FVector(0, 1, 0), FVector(1, 1, 0), FVector(1, 1, 1), FVector(0, 1, 1),
	FVector(0, 0, 0), FVector(0, 0, 1), FVector(1, 0, 1), FVector(1, 0, 0),
	FVector(0, 0, 0), FVector(1, 0, 0), FVector(1, 1, 0), FVector(0, 1, 0),
	FVector(0, 0, 1), FVector(0, 1, 1), FVector(1, 1, 1), FVector(1, 0, 1),
	FVector(0, 0, 0), FVector(0, 1, 0), FVector(0, 1, 1), FVector(0, 0, 1),
	FVector(1, 0, 0), FVector(1, 0, 1), FVector(1, 1, 1), FVector(1, 1, 0),
};
static const FIntVector BlockForwardDirections[6] =
{
	FIntVector(0, 1, 0), // east
	FIntVector(0, -1, 0), // west
	FIntVector(0, 0, -1), // bottom
	FIntVector(0, 0, 1), // top
	FIntVector(-1, 0, 0), // south
	FIntVector(1, 0, 0) // north
};

static const FVector BlockForwardVectors[6] =
{
	FVector(0, 1, 0),
	FVector(0, -1, 0),
	FVector(0, 0, -1),
	FVector(0, 0, 1),
	FVector(-1, 0, 0),
	FVector(1, 0, 0)
};

static const FVector BlockUpVectors[6] =
{
	FVector::UpVector * -1.0f,
	FVector::UpVector * -1.0f,
	FVector::ForwardVector,
	FVector::ForwardVector * -1.0f,
	FVector::UpVector * -1.0f,
	FVector::UpVector * -1.0f
};

static const FVector BlockRightVectors[6] =
{
	FVector::ForwardVector,
	FVector::ForwardVector * -1.0f,
	FVector::RightVector,
	FVector::RightVector,
	FVector::RightVector,
	FVector::RightVector * -1.0f
};
static const uint8 BlockDirectionAxis[6] = { 1, 1, 2, 2, 0, 0 };


FIntVector GetAdjacentCoordinate(FIntVector x, uint8 Side)
{
	return x + BlockForwardDirections[Side];
}
FBlockFace FChunkGenerator::GetBlockFace(const FIntVector& InCoordinate, uint8 Side) const
{

	uint8 BlockType = Chunk->GetBlock(InCoordinate).Active;

	FBlockFace Face;
	Face.Side = Side;
	Face.bCulled = BlockType == 0;
	Face.Type = BlockType;

	if (!Face.bCulled)
	{
		FIntVector AdjacentCoordinate = GetAdjacentCoordinate(InCoordinate, Side);
		uint8 AdjacentBlockType = Chunk->GetBlock(AdjacentCoordinate).Active;

		if (AdjacentBlockType != 0)
		{
			Face.bCulled = true;
		}
	}

	return Face;
}

void FChunkGenerator::Generate()
{
	FVector VolumeSize = FVector(16, 16, 128);

	TArray<FMeshData> MeshData;
	//TSet<UMaterialInterface*> Materials;
	MeshData.AddDefaulted();

	int32 UAxis = 0;
	int32 VAxis = 0;
	int32 FaceWidth = 0;
	int32 FaceHeight = 0;
	FIntVector BlockPosition;
	FIntVector BlockOffset;

	FBlockFace FaceA;
	FBlockFace FaceB;

	TArray<FBlockFace> BlockFaceMask;
	BlockFaceMask.SetNum(VolumeSize.X * VolumeSize.Y * VolumeSize.Z);

	FLinearColor Col = FLinearColor::MakeRandomColor();

	for (int32 FaceSide = 0; FaceSide < 6; ++FaceSide)
	{
		int32 Axis = BlockDirectionAxis[FaceSide];

		// 2 other axis
		UAxis = (Axis + 1) % 3;
		VAxis = (Axis + 2) % 3;

		BlockPosition = FIntVector(0, 0, 0);
		BlockOffset = BlockForwardDirections[FaceSide];

		// loop through the current axis
		for (BlockPosition[Axis] = 0; BlockPosition[Axis] < VolumeSize[Axis]; ++BlockPosition[Axis])
		{
			int32 MaskIndex = 0;
			bool bMaskEmpty = true;

			for (BlockPosition[VAxis] = 0; BlockPosition[VAxis] < VolumeSize[VAxis]; ++BlockPosition[VAxis])
			{
				for (BlockPosition[UAxis] = 0; BlockPosition[UAxis] < VolumeSize[UAxis]; ++BlockPosition[UAxis])
				{
					FaceB.bCulled = true;
					FaceB.Side = FaceSide;
					FaceB.Type = 0;

					// face of this block
					FaceA = GetBlockFace(BlockPosition, FaceSide);

					if ((BlockPosition[Axis] + BlockOffset[Axis]) < VolumeSize[Axis])
					{
						// adjacent face on axis
						FaceB = GetBlockFace(BlockPosition + BlockOffset, FaceSide);
					}

					if (!FaceA.bCulled && !FaceB.bCulled && FaceA.Equals(FaceB))
					{
						BlockFaceMask[MaskIndex].bCulled = true;
					}
					else
					{
						BlockFaceMask[MaskIndex] = FaceA;

						if (!FaceA.bCulled)
						{
							// there's a face, so mask is not empty
							bMaskEmpty = false;
						}
					}

					MaskIndex++;
				}
			}

			if (bMaskEmpty)
			{
				// mask has no faces, no point going any further
				continue;
			}

			MaskIndex = 0;

			for (int32 VAxisIndex = 0; VAxisIndex < VolumeSize[VAxis]; ++VAxisIndex)
			{
				for (int32 UAxisIndex = 0; UAxisIndex < VolumeSize[UAxis];)
				{
					if (BlockFaceMask[MaskIndex].bCulled)
					{
						UAxisIndex++;
						MaskIndex++;

						// if this face doesn't exist then no face is added
						continue;
					}

					// calculate the face width by checking if adjacent face is the same
					for (FaceWidth = 1;
						UAxisIndex + FaceWidth < VolumeSize[UAxis] &&
						!BlockFaceMask[MaskIndex + FaceWidth].bCulled &&
						BlockFaceMask[MaskIndex + FaceWidth].Equals(BlockFaceMask[MaskIndex]);
						FaceWidth++);

					// calculate the face height by checking if adjacent face is the same

					bool bFinished = false;

					for (FaceHeight = 1; VAxisIndex + FaceHeight < VolumeSize[VAxis]; ++FaceHeight)
					{
						for (int32 FaceWidthIndex = 0; FaceWidthIndex < FaceWidth; ++FaceWidthIndex)
						{
							const FBlockFace& MaskFace = BlockFaceMask[MaskIndex + FaceWidthIndex + FaceHeight * VolumeSize[UAxis]];

							// face doesn't exist or there's a new type of face
							if (MaskFace.bCulled || !MaskFace.Equals(BlockFaceMask[MaskIndex]))
							{
								// finished, got the face height
								bFinished = true;

								break;
							}
						}

						if (bFinished)
						{
							// finished, got the face height
							break;
						}
					}

					if (!BlockFaceMask[MaskIndex].bCulled)
					{
						BlockPosition[UAxis] = UAxisIndex;
						BlockPosition[VAxis] = VAxisIndex;

						static int triangleIndices[6] = { 0, 1, 2, 2, 3, 0 };

						uint8 BlockSide = BlockFaceMask[MaskIndex].Side;
						uint8 BlockTypeIndex = BlockFaceMask[MaskIndex].Type;

						if (BlockTypeIndex > 1)
						{
							BlockTypeIndex = 1;
						}

						//UBlockType* BlockType = BlockTypeDatabase->BlockTypes[BlockTypeIndex];
						//UMaterialInterface* MeshMaterial = BlockType->Materials[BlockSide].Material;
						int32 MeshIndex = INDEX_NONE;


						MeshIndex = 0;
			

						TArray<FVector>& Vertices = MeshData[MeshIndex].Vertices;
						TArray<int32>& Triangles = MeshData[MeshIndex].Triangles;
						TArray<FVector>& Normals = MeshData[MeshIndex].Normals;
						TArray<FVector2D>& UV0 = MeshData[MeshIndex].UV0;
						TArray<FColor>& VertexColors = MeshData[MeshIndex].VertexColors;
						TArray<struct FRuntimeMeshTangent>& Tangents = MeshData[MeshIndex].Tangents;

						int32 NumIndices = Triangles.Num();

						for (int32 VertexIndex = 0; VertexIndex < 6; ++VertexIndex)
						{
							// base vertex position of face
							FVector vertexPosition = VertexOffsets[BlockSide * 4 + triangleIndices[VertexIndex]];

							// scale the vertex across the width and height of the face
							vertexPosition[UAxis] *= FaceWidth;
							vertexPosition[VAxis] *= FaceHeight;
							vertexPosition += FVector(BlockPosition);

							//FVector2D UV = BlockType->GetPointUV(vertexPosition, FVector::ZeroVector, UMapData::BlockUpVectors[BlockSide], UMapData::BlockRightVectors[BlockSide], BlockSide);

							//UV0.Add(UV);
							Vertices.Add(vertexPosition * FBlock::SIZE);
							Normals.Add(BlockForwardVectors[BlockSide]);
							VertexColors.Add(Col.ToFColor(false));

							Triangles.Add(NumIndices + VertexIndex);
						}
					}

					for (int32 FaceHeightIndex = 0; FaceHeightIndex < FaceHeight; ++FaceHeightIndex)
					{
						for (int32 FaceWidthIndex = 0; FaceWidthIndex < FaceWidth; ++FaceWidthIndex)
						{
							BlockFaceMask[MaskIndex + FaceWidthIndex + FaceHeightIndex * VolumeSize[UAxis]].bCulled = true;
						}
					}

					UAxisIndex += FaceWidth;
					MaskIndex += FaceWidth;
				}
			}
		}
	}

	for (int32 Index = 0; Index < MeshData.Num(); ++Index)
	{
		TArray<FVector>& Vertices = MeshData[Index].Vertices;
		TArray<int32>& Triangles = MeshData[Index].Triangles;
		TArray<FVector>& Normals = MeshData[Index].Normals;
		TArray<FVector2D>& UV0 = MeshData[Index].UV0;
		TArray<FColor>& VertexColors = MeshData[Index].VertexColors;
		TArray<struct FRuntimeMeshTangent>& Tangents = MeshData[Index].Tangents;

		//MeshComponent->SetMaterial(Index, Materials[FSetElementId::FromInteger(Index)]);
		Mesh->CreateMeshSection(0, Vertices, Triangles, Normals, UV0, VertexColors, Tangents, true);
	}

	//Mesh->CreateMeshSection(0, Vertices, Triangles, Normals, TextureCoordinates, Colors, Tangents);
}

FChunkGenerator::FChunkGenerator(FChunk* TargetChunk, URuntimeMeshComponent* TargetMesh)
{
	Chunk = TargetChunk;
	Mesh = TargetMesh;






}
FChunkGenerator::~FChunkGenerator()
{
}
