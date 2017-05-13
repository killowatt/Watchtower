// Copyright 2017 William Yates

#include "Watchtower.h"
#include "VoxelPlayerController.h"

#include "OnlineTestGameMode.h"
#include "VoxelGameState.h"
#include "Chunk.h"
#include "Blueprint/UserWidget.h"

void AVoxelPlayerController::BeginPlay()
{
	Super::BeginPlay();
}

void AVoxelPlayerController::ServerTryModify_Implementation(FBlock Block)
{
	// Called on Server wowee
	UE_LOG(Voxel, Warning, TEXT("TryPlace Called _ Server"));
	UE_LOG(Voxel, Warning, TEXT("BlockData %s"), (Block.Active ? TEXT("True") : TEXT("False")));

	FVector Direction = PlayerCameraManager->GetCameraRotation().Vector();
	Direction.Normalize();

	FVector Position = PlayerCameraManager->GetCameraLocation();

	AVoxelGameState* gs = (AVoxelGameState*)GetWorld()->GetGameState();
	gs->MulticastChunkUpdate(Position, Direction, Block);
}
bool AVoxelPlayerController::ServerTryModify_Validate(FBlock Block)
{
	return true;
}

void AVoxelPlayerController::ServerBegin_Implementation()
{
	if (!serve && GetWorld()->GetNetMode() == NM_DedicatedServer)
	{
		TArray<uint8> CompressedData;
		FArchiveSaveCompressedProxy Compression(servdat, ECompressionFlags::COMPRESS_ZLIB);

		int32 TOTALSIZEWOW = (16 * 16 * 128) * 512;

		AVoxelGameState* gs = (AVoxelGameState*)GetWorld()->GetGameState();

		TArray<uint8> dat;
		dat.Append((uint8*)(gs->MapData->GetData()/* + (1024 * Index)*/), sizeof(FBlock) * TOTALSIZEWOW/*1024*/); // 16 is num blocks to send

		Compression << dat;

		Compression.Flush();

		if (Compression.GetError())
		{
			UE_LOG(Voxel, Error, TEXT("Compression error"));
		}

		finalChunkSize = servdat.Num() % 2048;
		TOTALCHUNKSz = (servdat.Num() - finalChunkSize) / 2048 + (finalChunkSize > 0);

		serve = true;
	}
	ClientBegin(TOTALCHUNKSz, finalChunkSize, FIntVector(16, 32, 0));
}
bool AVoxelPlayerController::ServerBegin_Validate()
{
	return true;
}
void AVoxelPlayerController::ClientBegin_Implementation(int32 TotalChunks, int32 ChunkSize, FIntVector Size)
{
	TOTALCHUNKSz = TotalChunks;
	finalChunkSize = ChunkSize;
	receivedChunks = 0;

	ServerAskChunk(0);

}
void AVoxelPlayerController::ServerAskChunk_Implementation(int32 Index)
{
	UE_LOG(Voxel, Warning, TEXT("Received AskChunk Index %d"), Index);

	AVoxelGameState* gs = (AVoxelGameState*)GetWorld()->GetGameState();

	// TESTING COMPRESSION
	TArray<uint8> send;

	int32 apndSize = 0;
	if (Index >= TOTALCHUNKSz && finalChunkSize > 0)
		apndSize = finalChunkSize;
	else
		apndSize = 2048;

	send.Append(servdat.GetData() + (2048 * Index), apndSize);
	//

	UE_LOG(Voxel, Warning, TEXT("Sent compressed packet of size %d"), send.Num());

	ClientSendChunk(send, Index);
}
bool AVoxelPlayerController::ServerAskChunk_Validate(int32 Index)
{
	return true;
}
void AVoxelPlayerController::ClientSendChunk_Implementation(const TArray<uint8>& bytes, int32 inde)
{
	UE_LOG(Voxel, Warning, TEXT("Recv compressed packet of size %d"), recvDat.Num());

	int32 appndSize = 0;
	if (receivedChunks >= TOTALCHUNKSz && finalChunkSize > 0)
		appndSize = finalChunkSize;
	else
		appndSize = 2048;

	recvDat.Append(bytes.GetData(), appndSize);

	UE_LOG(Voxel, Warning, TEXT("Chunk %d / %d"), receivedChunks, TOTALCHUNKSz);

	receivedChunks++;

	if (receivedChunks < TOTALCHUNKSz)
	{
		ServerAskChunk(receivedChunks);
	}
	else
	{
		UE_LOG(Voxel, Warning, TEXT("Supposedely got all the blocks lad"));
		AVoxelGameState* gs = (AVoxelGameState*)GetWorld()->GetGameState();

		TArray<uint8> decompressed;
		FArchiveLoadCompressedProxy Decompression(recvDat, ECompressionFlags::COMPRESS_ZLIB);

		if (Decompression.GetError())
		{
			UE_LOG(Voxel, Error, TEXT("Decompression error"));
		}

		Decompression << decompressed;

		Decompression.Flush();

		int32 TOTALSIZEWOW = (16 * 16 * 128) * 512;
		itsTheBlockZone.Append((FBlock*)decompressed.GetData(), TOTALSIZEWOW);

		UE_LOG(Voxel, Warning, TEXT("BLOCKS APPENDED"));

		gs->MapData = NewObject<UVoxelMapData>();
		gs->MapData->LoadFromBlocks(itsTheBlockZone, FIntVector(16 * 16, 16 * 32, 128));

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

		UE_LOG(Voxel, Warning, TEXT("CHUNK ACTORS CREATED"));
	}
}

AVoxelPlayerController::AVoxelPlayerController(const FObjectInitializer& ObjectInitializer) :
	Super(ObjectInitializer)
{
	bReplicates = true;
}