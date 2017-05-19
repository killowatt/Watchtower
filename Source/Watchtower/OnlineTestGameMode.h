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
	//virtual APlayerController* Login(UPlayer* NewPlayer, ENetRole InRemoteRole,
	//	const FString& Portal, const FString& Options, const FUniqueNetIdRepl& UniqueId,
	//	FString& ErrorMessage) override;

	virtual void PostLogin(APlayerController* NewPlayer) override;
	virtual void StartPlay() override;

	AOnlineTestGameMode(const FObjectInitializer& ObjectInitializer);
};
