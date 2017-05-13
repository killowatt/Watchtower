// Copyright 2017 William Yates

#include "Watchtower.h"
#include "VoxelPlayerState.h"

FText AVoxelPlayerState::GetHealthString()
{
	return FText();
}

AVoxelPlayerState::AVoxelPlayerState(const FObjectInitializer& ObjectInitializer) :
	Super(ObjectInitializer)
{
	bReplicates = true;
}


