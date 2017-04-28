// Copyright 2017 William Yates

#include "Watchtower.h"
#include "VoxelPlayer.h"

#include "Chunk.h"
#include "VoxelMapData.h"
#include "VoxelPlayer.h"
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
}

// Called every frame
void AVoxelPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
