// Copyright Yooshley. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "BequestAbilitySystemComponent.generated.h"

/**
 * 
 */

UCLASS()
class BEQUEST_API UBequestAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:
	UBequestAbilitySystemComponent();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Bequest|AbilitySystem")
	TArray<TSubclassOf<UGameplayAbility>> AbilitySet;

	UFUNCTION(BlueprintCallable, Category="Bequest|AbilitySystem")
	void InitializeAbilitySystem(AActor* InOwningActor, AActor* InAvatarActor);
	
	UFUNCTION(BlueprintCallable, Category="Bequest|AbilitySystem", meta=(ApplyLevel = "1"))
	void GrantAbilities(TArray<TSubclassOf<UGameplayAbility>> Abilities, int32 ApplyLevel);

	UFUNCTION(BlueprintCallable, Category="Bequest|AbilitySystem")
	void RemoveAbilities(TArray<TSubclassOf<UGameplayAbility>> Abilities);
	
	UFUNCTION(BlueprintCallable, Category="Bequest|AbilitySystem")
	bool TryActivateAbilityByTag(FGameplayTag Tag);
	
protected:
    	bool bIsAbilitySystemInitialized = false;
};
