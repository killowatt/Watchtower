// Copyright 2017 William Yates

#include "Watchtower.h"
#include "VoxelPlayerState.h"

AVoxelPlayerState::AVoxelPlayerState(const FObjectInitializer& ObjectInitializer) :
	Super(ObjectInitializer)
{
	bReplicates = true;

	Health = 100;
}


