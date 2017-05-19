// Copyright 2017 William Yates

#pragma once

#include "GameFramework/PlayerController.h"
#include "VoxelMapData.h"
#include "VoxelPlayerHUD.h"
#include "VoxelPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class WATCHTOWER_API AVoxelPlayerController : public APlayerController
{
	GENERATED_BODY()
	
//private:
	//bool PressedJump;

public:
	virtual void BeginPlay() override;

	UFUNCTION(Server, reliable, WithValidation)
	void ServerTryModify(FBlock Block);

	UFUNCTION(Server, reliable, WithValidation)
	void ServerShoot();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
	TSubclassOf<class UUserWidget> wowHUD;

	UUserWidget* balls;

	UVoxelPlayerHUD* PlayerHUD;

	bool FINALLYFINISHED;

public:
	// chunk retrieval code wow!
	UPROPERTY()
	int32 TOTALCHUNKSz;
	UPROPERTY()
	int32 finalChunkSize;

	int32 receivedChunks;
	TArray<uint8> recvDat;
	TArray<FBlock> itsTheBlockZone;

	// serv
	TArray<uint8> servdat;
	bool serve;

	UFUNCTION(Client, reliable)
	void ClientBegin(int32 TotalChunks, int32 ChunkSize, FIntVector Size);

	UFUNCTION(Server, reliable, WithValidation)
	void ServerBegin();

	UFUNCTION(Server, Reliable, WithValidation)
	void ServerAskChunk(int32 Index);

	UFUNCTION(Client, Reliable)
	void ClientSendChunk(const TArray<uint8>& bytes, int32 inde);

//public:

	AVoxelPlayerController(const FObjectInitializer& ObjectInitializer);
};
