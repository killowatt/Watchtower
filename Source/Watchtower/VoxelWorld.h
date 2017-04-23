// Copyright 2016 William Yates

#pragma once

#include "VoxelMapData.h"

#include "GameFramework/Actor.h"
#include "VoxelWorld.generated.h"

UCLASS()
class WATCHTOWER_API AVoxelWorld : public AActor
{
	GENERATED_BODY()
	
public:	
	UVoxelMapData MapData;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Sets default values for this actor's properties
	AVoxelWorld();
};
