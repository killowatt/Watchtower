// Copyright 2017 William Yates

#include "Watchtower.h"
#include "VoxelMapData.h"
#include "VoxelMath.h"
#include "Chunk.h"

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

bool UVoxelMapData::Callback(FIntVector Copy, FIntVector Face, FVector Direction, FBlock Block)
{
	if (GetBlock(Copy).Active)
	{
		if (Block.Active)
			Copy += Face;

		int32 ChunkX = FMath::FloorToInt(Copy.X / ChunkWidth);
		int32 ChunkY = FMath::FloorToInt(Copy.Y / ChunkDepth);

		int32 ChunkIndex = 32 * ChunkX + ChunkY;
		if (Chunks.IsValidIndex(ChunkIndex))
		{

			GetBlock(Copy) = Block;
			Chunks[ChunkIndex]->PleaseUpdate = true;
			return true;
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("Invalid Chunk Index"));
			return false;
		}
	}
	return false;
}
void UVoxelMapData::TryRaycastModify(FVector Direction, FVector Position, float Radius, FBlock Block)
{
	Position /= FBlock::Size;
	// do this better ^?

	FIntVector IntPosition = FIntVector(
		FMath::FloorToInt(Position.X),
		FMath::FloorToInt(Position.Y),
		FMath::FloorToInt(Position.Z));

	FVector Step = FVector(
		FMath::Sign(Direction.X),
		FMath::Sign(Direction.Y),
		FMath::Sign(Direction.Z));

	FVector Max = FVector(
		FVoxelMath::IntBound(Position.X, Direction.X),
		FVoxelMath::IntBound(Position.Y, Direction.Y),
		FVoxelMath::IntBound(Position.Z, Direction.Z));

	FVector Delta = Step / Direction;
	FIntVector Face = FIntVector::ZeroValue;

	if (Direction.IsZero())
		return; // TODO: log this?
		
	Radius /= FMath::Sqrt(
		Direction.X * Direction.X +
		Direction.Y * Direction.Y +
		Direction.Z * Direction.Z);

	while (
		(Step.X > 0 ? IntPosition.X < Size.X : IntPosition.X >= 0) &&
		(Step.Y > 0 ? IntPosition.Y < Size.Y : IntPosition.Y >= 0) &&
		(Step.Z > 0 ? IntPosition.Z < Size.Z : IntPosition.Z >= 0))
	{

		if (!(IntPosition.X < 0 || IntPosition.Y < 0 || IntPosition.Z < 0 ||
			IntPosition.X >= Size.X || IntPosition.Y >= Size.Y || IntPosition.Z >= Size.Z))
		{
			DrawDebugLine(GetWorld(), Position, Position + (Direction * 200), FColor::Red, false, 16, 0, 3.0f);
			DrawDebugPoint(GetWorld(), FVector(IntPosition.X, IntPosition.Y, IntPosition.Z), 5.0f, FColor::Red, false, 16, 0);
			if (Callback(IntPosition, Face, Direction, Block)) // callback
				break;
		}

		if (Max.X < Max.Y)
		{
			if (Max.X < Max.Z)
			{
				if (Max.X > Radius)
					break;

				IntPosition.X += Step.X;
				Max.X += Delta.X;

				Face = FIntVector(-Step.X, 0, 0);
			}
			else
			{
				if (Max.Z > Radius)
					break;

				IntPosition.Z += Step.Z;
				Max.Z += Delta.Z;

				Face = FIntVector(0, 0, -Step.Z);
			}
		}
		else
		{
			if (Max.Y < Max.Z)
			{
				if (Max.Y > Radius)
					break;

				IntPosition.Y += Step.Y;
				Max.Y += Delta.Y;

				Face = FIntVector(0, -Step.Y, 0);
			}
			else
			{
				// Identical to the second case, repeated for simplicity in
				// the conditionals.
				if (Max.Z > Radius)
					break;
				IntPosition.Z += Step.Z;
				Max.Z += Delta.Z;

				Face = FIntVector(0, 0, -Step.Z);
			}
		}
	}
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
	//Blocks.SetNum(64 * 64 * 128);
	//Size = FIntVector(64, 64, 128);

	//for (int32 x = 0; x < 64; x++)
	//{
	//	for (int32 y = 0; y < 64; y++)
	//	{
	//		int32 level = FMath::RandRange(0, 255);
	//		for (int32 z = 0; z < 128; z++)
	//		{
	//			Blocks[GetBlockIndex(x, y, z)].Active = true;
	//			Blocks[GetBlockIndex(x, y, z)].Color = FColor(z * 2, 30, 155, 255);
	//			Blocks[GetBlockIndex(x, y, z)].Color = FColor(level, 155, 255);
	//		}
	//	}
	//}

	//Layla's

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

	FColor colorpal[] = {
		FColor(255, 0, 0, 255),
		FColor(0, 255, 0, 255),
		FColor(0, 0, 255, 255),
		FColor(255, 255, 0, 255),
		FColor(0, 255, 255, 255),
		FColor(64, 0, 0, 255),
		FColor(0, 0, 0, 255),
		FColor(255, 255, 255, 255) };


	for (int32 x = 0; x < BlockData.Num(); x++)
	{
		Blocks[x].Active = BlockData[x] > 0;
		uint8 type = BlockData[x];

		if (type > 0)
		{
			if (type > 7)
			{
				Blocks[x].Color = FColor::Magenta;
			}
			else
			{
				Blocks[x].Color = colorpal[type];
			}
		}
	}
}

UVoxelMapData::UVoxelMapData()
{
}
UVoxelMapData::~UVoxelMapData()
{
}
