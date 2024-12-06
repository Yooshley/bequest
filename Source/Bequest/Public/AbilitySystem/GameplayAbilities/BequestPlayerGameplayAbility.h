// Copyright Yooshley. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "InputAction.h"
#include "AbilitySystem/GameplayAbilities/BequestGameplayAbilityBase.h"
#include "BequestPlayerGameplayAbility.generated.h"

class ABequestPlayerCharacter;

/**
 * 
 */
UCLASS()
class BEQUEST_API UBequestPlayerGameplayAbility : public UBequestGameplayAbilityBase
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Bequest|Ability Settings")
	bool bActivateAbilityOnInput = false;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Bequest|Input", meta = (EditCondition = "bActivateAbilityOnInput"))
	UInputAction* ActivationInputAction = nullptr;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Bequest|Input", meta = (EditCondition = "bActivateAbilityOnInput"))
	ETriggerEvent InputPressedTriggerType = ETriggerEvent::Started;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Bequest|Input", meta = (EditCondition = "bActivateAbilityOnInput"))
	ETriggerEvent InputReleasedTriggerType = ETriggerEvent::Completed;

	UFUNCTION(BlueprintCallable, BlueprintPure)
	ABequestPlayerCharacter* GetBequestPlayerCharacter() const { return QuestPlayerCharacter.Get(); }

protected:
	TWeakObjectPtr<ABequestPlayerCharacter> QuestPlayerCharacter = nullptr;
	
	virtual void OnAvatarSet(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;
	void SetupEnhancedInputBindings(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec);
	void HandleInputPressedEvent(const FInputActionValue& InputValue, const FGameplayAbilitySpecHandle SpecHandle);
	void HandleInputReleasedEvent(const FGameplayAbilitySpecHandle SpecHandle);
	virtual void OnRemoveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;

	
private:
	FInputActionValue CachedInputActionValue;

public:
	UFUNCTION(BlueprintCallable, Category = "Bequest|Input", meta = (EditCondition = "bActivateAbilityOnInput"))
	FInputActionValue GetCachedInputActionValue() const { return CachedInputActionValue; }
};
