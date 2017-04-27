// Copyright 2017 William Yates

#include "Watchtower.h"
#include "VoxelPlayer.h"

#include "Chunk.h"
#include "VoxelMapData.h"
#include "VoxelPlayer.h"
#include "VoxelPlayerController.h"

// Sets default values
AVoxelPlayer::AVoxelPlayer()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bReplicates = true;
	bReplicateMovement = true;
}

// Called when the game starts or when spawned
void AVoxelPlayer::BeginPlay()
{
	Super::BeginPlay();

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("VoxelPlayer"));
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("Building Chunk"));
	}

	UVoxelMapData* MapData = NewObject<UVoxelMapData>();
	MapData->Load("bin");

	FIntVector MapSize = MapData->GetSize();
	int32 RemainderX = MapSize.X % 16;
	int32 RemainderY = MapSize.Y % 16;

	int32 CompleteChunksX = (MapSize.X - RemainderX) / 16;
	int32 CompleteChunksY = (MapSize.Y - RemainderY) / 16;

	TArray<AChunk*> Chunks;

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

			Chunks.Add(Chunk);
		}
	}
}

// Called every frame
void AVoxelPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
