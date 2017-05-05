// Copyright 2017 William Yates

#pragma once

#include "GameFramework/PlayerController.h"
#include "VoxelMapData.h"
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

protected:
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

	UFUNCTION(Server, reliable, WithValidation)
	void ServerTryModify(FBlock Block);

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
	virtual void SetupInputComponent() override;

	AVoxelPlayerController(const FObjectInitializer& ObjectInitializer);
};
