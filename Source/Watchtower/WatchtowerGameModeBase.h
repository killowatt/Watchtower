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
	UPROPERTY()
	UVoxelMapData* MapData;

	AWatchtowerGameModeBase(const FObjectInitializer& ObjectInitializer);

	virtual void StartPlay() override;
};
