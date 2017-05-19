// Copyright 2017 William Yates

#include "Watchtower.h"
#include "VoxelChunkReceiver.h"


// Sets default values
AVoxelChunkReceiver::AVoxelChunkReceiver()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AVoxelChunkReceiver::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AVoxelChunkReceiver::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

