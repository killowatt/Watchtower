// Copyright 2017 William Yates

#pragma once

#include "GameFramework/PlayerController.h"
#include "VoxelPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class WATCHTOWER_API AVoxelPlayerController : public APlayerController
{
	GENERATED_BODY()
	
private:
	bool PressedJump;

protected:
	UFUNCTION()
		void MoveForward(float Value);
	UFUNCTION()
		void MoveRight(float Value);

	UFUNCTION()
		void OnStartJump();
	UFUNCTION()
		void OnStopJump();

public:
	virtual void SetupInputComponent() override;

	AVoxelPlayerController(const FObjectInitializer& ObjectInitializer);
};
