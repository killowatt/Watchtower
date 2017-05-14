// Copyright 2017 William Yates

#include "Watchtower.h"
#include "VoxelPlayerHUD.h"
#include "VoxelPlayerState.h"

void UVoxelPlayerHUD::NativeTick(const FGeometry& MyGeometry, float DeltaTime)
{
	Super::Tick(MyGeometry, DeltaTime);

	if (Player)
	{
		if (!Player->PlayerState)
			return;

		AVoxelPlayerState* PlayerState = (AVoxelPlayerState*)Player->PlayerState;

		if (!Health.EqualTo(FText::AsNumber(PlayerState->Health)))
			Health = FText::AsNumber(PlayerState->Health);
	}
}
void UVoxelPlayerHUD::SetPlayerReference(const ACharacter* PlayerReference)
{
	Player = PlayerReference;
}

UVoxelPlayerHUD::UVoxelPlayerHUD(const FObjectInitializer& ObjectInitializer) :
	Super(ObjectInitializer)
{
	bCanEverTick = true;

	bShowLoading = true; // TODO: ty
}

