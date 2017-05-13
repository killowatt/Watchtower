// Copyright 2017 William Yates

#pragma once

#include "GameFramework/PlayerState.h"
#include "VoxelPlayerState.generated.h"

/**
 * 
 */
UENUM()
enum class ENetClientState
{
	None,
	ReceivingMap,
	Connected
};

UCLASS()
class WATCHTOWER_API AVoxelPlayerState : public APlayerState
{
	GENERATED_BODY()
	
public:
	static const int32 MaxHealth = 100;

	UPROPERTY()
	int32 Health;

	UFUNCTION()
	FText GetHealthString();

	UPROPERTY()
	ENetClientState State;

	
	AVoxelPlayerState(const FObjectInitializer& ObjectInitializer);
};
