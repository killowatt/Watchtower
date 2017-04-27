// Copyright 2017 William Yates

#pragma once

#include "GameFramework/GameModeBase.h"
#include "VoxelPlayerController.h"
#include "OnlineTestGameMode.generated.h"

/**
 * 
 */
UCLASS()
class WATCHTOWER_API AOnlineTestGameMode : public AGameModeBase
{
	GENERATED_BODY()

	TArray<APlayerController*> PlayerControllers;

public:
	virtual void PostLogin(APlayerController* NewPlayer) override;

	AOnlineTestGameMode(const FObjectInitializer& ObjectInitializer);
};
