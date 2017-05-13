// Copyright 2017 William Yates

#include "Watchtower.h"
#include "VoxelPlayer.h"

#include "Chunk.h"
#include "VoxelMapData.h"
#include "VoxelPlayerController.h"

// Sets default values
AVoxelPlayer::AVoxelPlayer()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bReplicates = true;
	bReplicateMovement = true;
}

// Called when the game starts or when spawned
void AVoxelPlayer::BeginPlay()
{
	Super::BeginPlay();

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("VoxelPlayer"));

	}

	if (GetWorld()->GetNetMode() == NM_Client)
	{

		PlayerHUD = CreateWidget<UVoxelPlayerHUD>(GetWorld(), wowHUD);

		if (PlayerHUD)
			PlayerHUD->AddToViewport();
	}

}

void AVoxelPlayer::SetupPlayerInputComponent(UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

	InputComponent->BindAxis("MoveForward", this, &AVoxelPlayer::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &AVoxelPlayer::MoveRight);
	InputComponent->BindAxis("LookX", this, &AVoxelPlayer::AddControllerYawInput);
	InputComponent->BindAxis("LookY", this, &AVoxelPlayer::AddControllerPitchInput);

	InputComponent->BindAction("Primary", IE_Pressed, this, &AVoxelPlayer::Primary);
	InputComponent->BindAction("Secondary", IE_Pressed, this, &AVoxelPlayer::Secondary);
	InputComponent->BindAction("Jump", IE_Pressed, this, &AVoxelPlayer::OnStartJump);
	InputComponent->BindAction("Jump", IE_Released, this, &AVoxelPlayer::OnStopJump);
}

void AVoxelPlayer::MoveForward(float Value)
{
	if (Controller && Value != 0.0f)
	{
		// find out which way is forward
		FRotator Rotation = Controller->GetControlRotation();
		// Limit pitch when walking or falling
		if (GetCharacterMovement()->IsMovingOnGround() || GetCharacterMovement()->IsFalling())
		{
			Rotation.Pitch = 0.0f;
		}
		// add movement in that direction

		UE_LOG(Voxel, Warning, TEXT("Movement is %f"), Value);

		const FVector Direction = FRotationMatrix(Rotation).GetScaledAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}
void AVoxelPlayer::MoveRight(float Value)
{
	if (Controller && Value != 0.0f)
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FVector Direction = FRotationMatrix(Rotation).GetScaledAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}

void AVoxelPlayer::Primary()
{
	FBlock Block = FBlock();
	Block.Color = FColor::Blue;
	Block.Active = false;
	
	((AVoxelPlayerController*)Controller)->ServerTryModify(Block);

	UE_LOG(Voxel, Warning, TEXT("BlockData %s"), (Block.Active ? TEXT("True") : TEXT("False")));
	//AWatchtowerGameModeBase* gm = (AWatchtowerGameModeBase*)GetWorld()->GetAuthGameMode();
	//UVoxelMapData* MapData = gm->MapData;

	//FVector Direction = PlayerCameraManager->GetCameraRotation().Vector();
	//Direction.Normalize();


	//FBlock x = FBlock();
	//x.Active = false;

	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue,
	//	TEXT("Direction " + Direction.ToString()));

	//DrawDebugLine(GetWorld(), PlayerCameraManager->GetCameraLocation(), PlayerCameraManager->GetCameraLocation() + (Direction * 200), FColor::Green, false, 16, 0, 3.0f);

	//MapData->TryRaycastModify(Direction, PlayerCameraManager->GetCameraLocation(), 8, x);
}
void AVoxelPlayer::Secondary()
{
	FBlock Block = FBlock();
	Block.Color = FColor::Blue;
	Block.Active = true;

	((AVoxelPlayerController*)Controller)->ServerTryModify(Block);

	UE_LOG(Voxel, Warning, TEXT("BlockData %s"), (Block.Active ? TEXT("True") : TEXT("False")));
	//AWatchtowerGameModeBase* gm = (AWatchtowerGameModeBase*)GetWorld()->GetAuthGameMode();
	//UVoxelMapData* MapData = gm->MapData;

	//FVector Direction = PlayerCameraManager->GetCameraRotation().Vector();
	//Direction.Normalize();

	//FBlock x = FBlock();
	//x.Active = true;
	//x.Color = FColor(218, 165, 32);

	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue,
	//	TEXT("Direction " + Direction.ToString()));

	//MapData->TryRaycastModify(Direction, PlayerCameraManager->GetCameraLocation(), 8, x);
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
