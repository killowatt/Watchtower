// Copyright 2017 William Yates

#pragma once

#include "Blueprint/UserWidget.h"
#include "VoxelPlayerHUD.generated.h"

/**
 * 
 */
UCLASS()
class WATCHTOWER_API UVoxelPlayerHUD : public UUserWidget
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText Health;
	

	UVoxelPlayerHUD(const FObjectInitializer& ObjectInitializer);
};
