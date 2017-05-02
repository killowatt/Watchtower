// Copyright 2017 William Yates

#pragma once

#include "GameFramework/GameStateBase.h"
#include "VoxelMapData.h"
#include "VoxelGameState.generated.h"

/**
 * 
 */
UCLASS()
class WATCHTOWER_API AVoxelGameState : public AGameStateBase
{
	GENERATED_BODY()
	
public:
	UPROPERTY()
	UVoxelMapData* MapData;

	bool bgenned;

	UFUNCTION(NetMulticast, Reliable)
	void MulticastChunkUpdate(FVector Position, FVector Direction, FBlock bl);

	AVoxelGameState();
};


