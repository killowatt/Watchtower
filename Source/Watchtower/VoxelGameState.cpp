// Copyright 2017 William Yates

#include "Watchtower.h"
#include "Chunk.h"
#include "VoxelGameState.h"

void AVoxelGameState::MulticastChunkUpdate_Implementation(FVector Position, FVector Direction,
	FBlock bl)
{
	UE_LOG(Voxel, Warning, TEXT("Multicast called"));

	if (!MapData)
		UE_LOG(Voxel, Error, TEXT("MapData was null. Brace for impact"));

	MapData->TryRaycastModify(Direction, Position, 8, bl);
}



AVoxelGameState::AVoxelGameState()
{
	bgenned = false;
}





