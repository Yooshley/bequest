// Copyright Yooshley. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "BequestAbilitySystemComponent.generated.h"

/**
 * 
 */

class UDataAsset_AbilitySystem;

UCLASS()
class BEQUEST_API UBequestAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:
	UBequestAbilitySystemComponent();

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Bequest|AbilitySystem")
	UDataTable* AttributeDataTable;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Bequest|AbilitySystem")
	TSoftObjectPtr<UDataAsset_AbilitySystem> AbilitySystemData;
	
	void InitializeAbilitySystem(AActor* InOwningActor, AActor* InAvatarActor);
	const UAttributeSet* GetOrCreateAttributeSet(const TSubclassOf<UAttributeSet>& AttributeSet);
	
	UFUNCTION(BlueprintCallable, Category="Bequest|AbilitySystem")
	void LoadAbilityData(TSoftObjectPtr<UDataAsset_AbilitySystem> InAbilityDataAsset, UDataTable* InAttributeDataTable);
	
	UFUNCTION(BlueprintCallable, Category="Bequest|AbilitySystem", meta=(ApplyLevel = "1"))
	void GrantAbilities(TArray<TSubclassOf<UGameplayAbility>> Abilities, int32 ApplyLevel);

	UFUNCTION(BlueprintCallable, Category="Bequest|AbilitySystem")
	void RemoveAbilities(TArray<TSubclassOf<UGameplayAbility>> Abilities);
	
	UFUNCTION(BlueprintCallable, Category="Bequest|AbilitySystem")
	bool TryActivateAbilityByTag(FGameplayTag Tag);
	
protected:
	bool bIsAbilitySystemInitialized = false;
};
