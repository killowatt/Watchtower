// Copyright 2017 William Yates

#pragma once

#include "GameFramework/GameStateBase.h"
#include "VoxelGameState.generated.h"

/**
 * 
 */
UCLASS()
class WATCHTOWER_API AVoxelGameState : public AGameStateBase
{
	GENERATED_BODY()
	
public:
	UFUNCTION(NetMulticast, Reliable)
	void MulticastChunkUpdate();
	
	
};
