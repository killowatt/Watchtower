// Copyright 2017 William Yates

#pragma once

#include "GameFramework/Character.h"
#include "VoxelPlayer.generated.h"

UCLASS()
class WATCHTOWER_API AVoxelPlayer : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AVoxelPlayer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void MoveForward(float Val);
	UFUNCTION()
	void MoveRight(float Val);

	UFUNCTION()
	void OnStartJump();
	UFUNCTION()
	void OnStopJump();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	
	
};
