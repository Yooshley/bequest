// Copyright Yooshley. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "DataAsset_AbilityData.generated.h"

class UGameplayAbility;

/**
 * 
 */
UCLASS()
class BEQUEST_API UDataAsset_AbilityData : public UDataAsset
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Bequest|AbilitySystem")
	TArray<TSubclassOf<UGameplayAbility>> AbilitySet;

public:
	FORCEINLINE TArray<TSubclassOf<UGameplayAbility>> GetAbilitySet() { return AbilitySet; }
};
