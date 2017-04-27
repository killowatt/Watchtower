// Copyright 2017 William Yates

#pragma once

#include "GameFramework/Character.h"
#include "VoxelPlayer.generated.h"

UCLASS()
class WATCHTOWER_API AVoxelPlayer : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AVoxelPlayer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
