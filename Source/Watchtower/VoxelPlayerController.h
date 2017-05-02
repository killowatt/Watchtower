// Copyright 2017 William Yates

#pragma once

#include "GameFramework/PlayerController.h"
#include "VoxelMapData.h"
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
	void Primary();
	UFUNCTION()
	void Secondary();

	UFUNCTION()
	void OnStartJump();
	UFUNCTION()
	void OnStopJump();

	UFUNCTION(Server, reliable, WithValidation)
	void ServerTryModify(FBlock Block);

public:
	virtual void SetupInputComponent() override;

	AVoxelPlayerController(const FObjectInitializer& ObjectInitializer);
};
