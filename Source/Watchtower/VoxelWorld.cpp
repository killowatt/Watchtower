// Copyright 2016 William Yates

#include "Watchtower.h"
#include "VoxelWorld.h"

// Called when the game starts or when spawned
void AVoxelWorld::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AVoxelWorld::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

// Sets default values
AVoxelWorld::AVoxelWorld()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

