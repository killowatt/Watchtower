// Copyright 2017 William Yates

#pragma once

#include "GameFramework/PlayerState.h"
#include "VoxelPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class WATCHTOWER_API AVoxelPlayerState : public APlayerState
{
	GENERATED_BODY()
	
public:
	static const int32 MaxHealth = 100;

	int32 Health;
	
	
};
