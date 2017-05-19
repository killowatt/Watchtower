// Copyright 2017 William Yates

#pragma once

#include "GameFramework/Actor.h"
#include "VoxelChunkReceiver.generated.h"

UCLASS()
class WATCHTOWER_API AVoxelChunkReceiver : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AVoxelChunkReceiver();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	
};
