// Copyright 2017 William Yates

#include "Watchtower.h"
#include "VoxelPlayer.h"


// Sets default values
AVoxelPlayer::AVoxelPlayer()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AVoxelPlayer::BeginPlay()
{
	Super::BeginPlay();

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("VoxelPlayer"));
	}


}
void AVoxelPlayer::SetupPlayerInputComponent(UInputComponent* InputComponent)
{
	// set up gameplay key bindings
	InputComponent->BindAxis("MoveForward", this, &AVoxelPlayer::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &AVoxelPlayer::MoveRight);
	InputComponent->BindAxis("LookX", this, &AVoxelPlayer::AddControllerYawInput);
	InputComponent->BindAxis("LookY", this, &AVoxelPlayer::AddControllerPitchInput);
	InputComponent->BindAction("Jump", IE_Pressed, this, &AVoxelPlayer::OnStartJump);
	InputComponent->BindAction("Jump", IE_Released, this, &AVoxelPlayer::OnStopJump);
}

void AVoxelPlayer::MoveForward(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		// find out which way is forward
		FRotator Rotation = Controller->GetControlRotation();
		// Limit pitch when walking or falling
		if (GetCharacterMovement()->IsMovingOnGround() || GetCharacterMovement()->IsFalling())
		{
			Rotation.Pitch = 0.0f;
		}
		// add movement in that direction
		const FVector Direction = FRotationMatrix(Rotation).GetScaledAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}
void AVoxelPlayer::MoveRight(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FVector Direction = FRotationMatrix(Rotation).GetScaledAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}

void AVoxelPlayer::OnStartJump()
{
	bPressedJump = true;
}
void AVoxelPlayer::OnStopJump()
{
	bPressedJump = false;
}

// Called every frame
void AVoxelPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
