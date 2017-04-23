// Copyright 2017 William Yates

#include "Watchtower.h"
#include "WatchtowerGameModeBase.h"

#include "Chunk.h"

void AWatchtowerGameModeBase::StartPlay()
{
	Super::StartPlay();

	TArray<AChunk*> chunks;

	for (int x = 0; x < 64; x++)
	{
		for (int y = 0; y < 64; y++)
		{
			chunks.Add(GetWorld()->
				SpawnActor<AChunk>(FVector(x * 16 * 100, y * 16 * 100, 0), FRotator::ZeroRotator));
		}
	}
}