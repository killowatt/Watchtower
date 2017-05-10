// Copyright 2017 William Yates

#include "Watchtower.h"
#include "OnlineTestGameMode.h"

#include "Chunk.h"
#include "VoxelMapData.h"
#include "VoxelPlayer.h"
#include "VoxelPlayerController.h"
#include "VoxelPlayerState.h"
#include "VoxelGameState.h"

void AOnlineTestGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);



	//AVoxelPlayerController* Player = (AVoxelPlayerController*)NewPlayer;
	//Player->ServerBegin();


	//ClientSetupChunks();

	//PlayerControllers.Add(NewPlayer);
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("Post Login Added"));
//
	//AVoxelPlayer* Player = GetWorld()->SpawnActor<AVoxelPlayer>();
	//NewPlayer->SetPawn(Player);
}
void AOnlineTestGameMode::StartPlay()
{
	if (GEngine->GetNetMode(GetWorld()) == NM_DedicatedServer)
	{
		AVoxelGameState* gs = (AVoxelGameState*)GetWorld()->GetGameState();
		if (!gs->bgenned)
		{
			gs->MapData = NewObject<UVoxelMapData>();
			gs->MapData->Load("bin");

			FIntVector MapSize = gs->MapData->GetSize();
			int32 RemainderX = MapSize.X % 16;
			int32 RemainderY = MapSize.Y % 16;

			int32 CompleteChunksX = (MapSize.X - RemainderX) / 16;
			int32 CompleteChunksY = (MapSize.Y - RemainderY) / 16;

			for (int X = 0; X < CompleteChunksX + (RemainderX > 0); X++)
			{
				for (int Y = 0; Y < CompleteChunksY + (RemainderY > 0); Y++)
				{
					FIntVector ChunkSize(16, 16, 128);
					if (X > CompleteChunksX)
						ChunkSize.X = RemainderX;
					if (Y > CompleteChunksY)
						ChunkSize.Y = RemainderY;

					AChunk* Chunk = GetWorld()->
						SpawnActor<AChunk>(FVector(X * 16 * 100, Y * 16 * 100, 0), FRotator::ZeroRotator);
					Chunk->SetRelativeMapData(gs->MapData, FIntVector(X * 16, Y * 16, 0), ChunkSize);
					Chunk->Generate();

					gs->MapData->Chunks.Add(Chunk);
				}
			}

			gs->bgenned = true;
			UE_LOG(Voxel, Warning, TEXT("Server successfully loaded chunks."));
		}
	}
}

AOnlineTestGameMode::AOnlineTestGameMode(const class FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	//DefaultPawnClass = AVoxelPlayer::StaticClass();
	PlayerControllerClass = AVoxelPlayerController::StaticClass();
	PlayerStateClass = AVoxelPlayerState::StaticClass();
	GameStateClass = AVoxelGameState::StaticClass();

	// temp, use commented above 
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnObject(TEXT("/Game/BP_VoxelPlayer"));
	if (PlayerPawnObject.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnObject.Class;
	}
}

