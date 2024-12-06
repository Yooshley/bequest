// Copyright Yooshley. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "BequestGameplayAbilityBase.generated.h"

class ABequestCharacterBase;
/**
 * 
 */
UCLASS()
class BEQUEST_API UBequestGameplayAbilityBase : public UGameplayAbility
{
	GENERATED_BODY()

public:
	UBequestGameplayAbilityBase();
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Bequest|Ability Settings")
	bool bActivateAbilityOnGrant = false;

	UFUNCTION(BlueprintCallable, BlueprintPure)
	ABequestCharacterBase* GetBequestCharacter() const { return QuestCharacter.Get(); }

protected:
	TWeakObjectPtr<ABequestCharacterBase> QuestCharacter = nullptr;

	virtual void OnAvatarSet(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;
};
