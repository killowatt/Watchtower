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

private:
	const APlayerController* Player;

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText Health;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText CurrentWeapon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ESlateVisibility Loading;

	virtual void NativeTick(const FGeometry& MyGeometry, float DeltaTime) override;

	void SetPlayerReference(const APlayerController* PlayerReference);

	UVoxelPlayerHUD(const FObjectInitializer& ObjectInitializer);
};
