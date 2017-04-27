// Copyright 2017 William Yates

#include "Watchtower.h"
#include "OnlineTestGameMode.h"

#include "Chunk.h"
#include "VoxelMapData.h"
#include "VoxelPlayer.h"
#include "VoxelPlayerController.h"

void AOnlineTestGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	//ClientSetupChunks();

	//PlayerControllers.Add(NewPlayer);
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("Post Login Added"));
//
	//AVoxelPlayer* Player = GetWorld()->SpawnActor<AVoxelPlayer>();
	//NewPlayer->SetPawn(Player);
}

AOnlineTestGameMode::AOnlineTestGameMode(const class FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	//DefaultPawnClass = AVoxelPlayer::StaticClass();
	PlayerControllerClass = AVoxelPlayerController::StaticClass();


	// temp, use commented above 
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnObject(TEXT("/Game/BP_VoxelPlayer"));
	if (PlayerPawnObject.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnObject.Class;
	}
}

