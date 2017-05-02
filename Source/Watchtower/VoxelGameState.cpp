// Copyright 2017 William Yates

#include "Watchtower.h"
#include "Chunk.h"
#include "VoxelGameState.h"

void AVoxelGameState::MulticastChunkUpdate_Implementation(FVector Position, FVector Direction,
	FBlock bl)
{
	UE_LOG(Voxel, Warning, TEXT("Multicast called"));

	if (!bgenned)
	{
		MapData = NewObject<UVoxelMapData>();
		MapData->Load("bin");

		FIntVector MapSize = MapData->GetSize();
		int32 RemainderX = MapSize.X % 16;
		int32 RemainderY = MapSize.Y % 16;

		int32 CompleteChunksX = (MapSize.X - RemainderX) / 16;
		int32 CompleteChunksY = (MapSize.Y - RemainderY) / 16;

		for (int X = 0; X < CompleteChunksX + (RemainderX > 0); X++)
		{
			for (int Y = 0; Y < CompleteChunksY + (RemainderY > 0); Y++)
			{
				FIntVector ChunkSize(16, 16, 128);
				if (X > CompleteChunksX)
					ChunkSize.X = RemainderX;
				if (Y > CompleteChunksY)
					ChunkSize.Y = RemainderY;

				AChunk* Chunk = GetWorld()->
					SpawnActor<AChunk>(FVector(X * 16 * 100, Y * 16 * 100, 0), FRotator::ZeroRotator);
				Chunk->SetRelativeMapData(MapData, FIntVector(X * 16, Y * 16, 0), ChunkSize);
				Chunk->Generate();

				MapData->Chunks.Add(Chunk);
			}
		}

		bgenned = true;
	}

	MapData->TryRaycastModify(Direction, Position, 8, bl);
}



AVoxelGameState::AVoxelGameState()
{
	bgenned = false;
}





