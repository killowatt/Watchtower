// Copyright 2017 William Yates

#include "Watchtower.h"
#include "VoxelPlayerState.h"
#include "UnrealNetwork.h"

void AVoxelPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AVoxelPlayerState, Health);
}

AVoxelPlayerState::AVoxelPlayerState(const FObjectInitializer& ObjectInitializer) :
	Super(ObjectInitializer)
{
	bReplicates = true;

	NetUpdateFrequency = 16;
	MinNetUpdateFrequency = 1;

	Health = 100;
}


