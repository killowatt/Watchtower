// Copyright 2017 William Yates

#include "Watchtower.h"
#include "VoxelPlayerController.h"
#include "WatchtowerGameModeBase.h"

void AVoxelPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAxis("MoveForward", this, &AVoxelPlayerController::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &AVoxelPlayerController::MoveRight);
	InputComponent->BindAxis("LookX", this, &AVoxelPlayerController::AddYawInput);
	InputComponent->BindAxis("LookY", this, &AVoxelPlayerController::AddPitchInput);

	InputComponent->BindAction("Primary", IE_Pressed, this, &AVoxelPlayerController::Primary);
	InputComponent->BindAction("Secondary", IE_Pressed, this, &AVoxelPlayerController::Secondary);
	InputComponent->BindAction("Jump", IE_Pressed, this, &AVoxelPlayerController::OnStartJump);
	InputComponent->BindAction("Jump", IE_Released, this, &AVoxelPlayerController::OnStopJump);
}

void AVoxelPlayerController::MoveForward(float Value)
{
	if (GetPawn() && Value != 0.0f)
	{
		// find out which way is forward
		FRotator Rotation = GetControlRotation();
		// Limit pitch when walking or falling
		if (GetPawn()->GetMovementComponent()->IsMovingOnGround() ||
			GetPawn()->GetMovementComponent()->IsFalling())
		{
			Rotation.Pitch = 0.0f;
		}
		// add movement in that direction
		const FVector Direction = FRotationMatrix(Rotation).GetScaledAxis(EAxis::X);
		GetPawn()->AddMovementInput(Direction, Value);
	}
}
void AVoxelPlayerController::MoveRight(float Value)
{
	if (GetPawn() && Value != 0.0f)
	{
		// find out which way is right
		const FRotator Rotation = GetControlRotation();
		const FVector Direction = FRotationMatrix(Rotation).GetScaledAxis(EAxis::Y);
		// add movement in that direction
		GetPawn()->AddMovementInput(Direction, Value);
	}
}
void AVoxelPlayerController::Primary()
{
	AWatchtowerGameModeBase* gm = (AWatchtowerGameModeBase*)GetWorld()->GetAuthGameMode();
	UVoxelMapData* MapData = gm->MapData;

	FVector Direction = PlayerCameraManager->GetCameraRotation().Vector();
	Direction.Normalize();

	FBlock x = FBlock();
	x.Active = false;

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue,
		TEXT("Direction X: " + Direction.ToString()));

	MapData->TryRaycastModify(Direction, PlayerCameraManager->GetCameraLocation(), 8, x);
}
void AVoxelPlayerController::Secondary()
{
	AWatchtowerGameModeBase* gm = (AWatchtowerGameModeBase*)GetWorld()->GetAuthGameMode();
	UVoxelMapData* MapData = gm->MapData;

	FVector Direction = PlayerCameraManager->GetCameraRotation().Vector();
	Direction.Normalize();

	FBlock x = FBlock();
	x.Active = true;
	x.Color = FColor(218, 165, 32);

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue,
		TEXT("Direction X: " + Direction.ToString()));

	MapData->TryRaycastModify(Direction, PlayerCameraManager->GetCameraLocation(), 8, x);
}
void AVoxelPlayerController::OnStartJump()
{
	if (GetCharacter())
		GetCharacter()->bPressedJump = true;
}
void AVoxelPlayerController::OnStopJump()
{
	if (GetCharacter())
		GetCharacter()->bPressedJump = false;
}

AVoxelPlayerController::AVoxelPlayerController(const FObjectInitializer& ObjectInitializer) :
	Super(ObjectInitializer)
{
	bReplicates = true;
}