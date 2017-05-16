// Copyright 2017 William Yates

#pragma once

#include "GameFramework/Character.h"
#include "VoxelPlayerHUD.h"
#include "VoxelPlayer.generated.h"

UCLASS()
class WATCHTOWER_API AVoxelPlayer : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AVoxelPlayer();


	bool weaponEnabled;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

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

	UFUNCTION()
		void PrimaryWeapon();
	UFUNCTION()
		void SecondaryWeapon();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
