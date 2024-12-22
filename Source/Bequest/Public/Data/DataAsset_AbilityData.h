// Copyright Yooshley. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "DataAsset_AbilityData.generated.h"

class UGameplayEffect;
class UAttributeSet;
class UGameplayAbility;

/**
 * 
 */
UCLASS()
class BEQUEST_API UDataAsset_AbilitySystem : public UDataAsset
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Bequest|AbilitySystem")
	TArray<TSubclassOf<UAttributeSet>> Attributes;
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Bequest|AbilitySystem")
	TArray<TSubclassOf<UGameplayAbility>> Abilities;
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Bequest|AbilitySystem")
	TArray<TSubclassOf<UGameplayEffect>> Effects;

public:
	FORCEINLINE TArray<TSubclassOf<UGameplayAbility>> GetAbilities() { return Abilities; }
	FORCEINLINE TArray<TSubclassOf<UAttributeSet>> GetAttributes() { return Attributes; }
	FORCEINLINE TArray<TSubclassOf<UGameplayEffect>> GetEffects() { return Effects; }
};
