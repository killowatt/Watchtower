// Copyright 2017 William Yates

#include "Watchtower.h"
#include "WatchtowerGameModeBase.h"

#include "Chunk.h"
#include "VoxelMapData.h"
#include "VoxelPlayer.h"
#include "VoxelPlayerController.h"

void AWatchtowerGameModeBase::StartPlay()
{
	Super::StartPlay();

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
	//for (int x = 0; x < 64; x++)
	//{
	//	for (int y = 0; y < 64; y++)
	//	{
	//		AChunk* chunk = GetWorld()->
	//			SpawnActor<AChunk>(FVector(x * 16 * 100, y * 16 * 100, 0), FRotator::ZeroRotator);
	//		chunk->SetRelativeMapData(MapData, FIntVector(x * 16, y * 16, 0), FIntVector(16, 16, 128));
	//		chunks.Add(chunk);
	//		chunk->Generate();
	//	}
	//}

}

AWatchtowerGameModeBase::AWatchtowerGameModeBase(const class FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	DefaultPawnClass = AVoxelPlayer::StaticClass();
	PlayerControllerClass = AVoxelPlayerController::StaticClass();

	MapData = nullptr;
	// temp, use commented above 
	//static ConstructorHelpers::FClassFinder<APawn> PlayerPawnObject(TEXT("/Game/BP_VoxelPlayer"));
	//if (PlayerPawnObject.Class != NULL)
	//{
	//	DefaultPawnClass = PlayerPawnObject.Class;
	//}
}