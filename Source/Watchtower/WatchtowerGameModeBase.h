// Copyright 2017 William Yates

#pragma once

#include "GameFramework/GameModeBase.h"
#include "VoxelMapData.h"
#include "WatchtowerGameModeBase.generated.h"
/**
 * 
 */
UCLASS()
class WATCHTOWER_API AWatchtowerGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	//UVoxelMapData MapData;

	virtual void StartPlay() override;
};
