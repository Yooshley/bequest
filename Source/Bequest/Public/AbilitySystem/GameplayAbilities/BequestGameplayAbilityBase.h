// Copyright Yooshley. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "Abilities/GameplayAbility.h"
#include "BequestGameplayAbilityBase.generated.h"

class UBequestEquipmentSystemComponent;
class UBequestAbilitySystemComponent;
enum class EBequestResultType : uint8;
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

	UFUNCTION(BlueprintPure, Category = "Bequest|Ability")
	UBequestEquipmentSystemComponent* GetEquipmentSystemComponent() const;

	UFUNCTION(BlueprintPure, Category = "Bequest|Ability")
	UBequestAbilitySystemComponent* GetAbilitySystemComponent() const;
	
	UFUNCTION(BlueprintPure, Category = "Bequest|Ability")
	FGameplayEffectSpecHandle GetDamageEffectSpecHandle(TSubclassOf<UGameplayEffect> Effect, float Damage, FGameplayTag TypeTag);

	FActiveGameplayEffectHandle NativeApplyEffectSpecHandleToTarget(AActor* TargetActor, const FGameplayEffectSpecHandle& SpecHandle);
	
	UFUNCTION(BlueprintCallable, Category = "Bequest|Ability", meta = (ExpandEnumAsExecs = "SuccessType"))
	FActiveGameplayEffectHandle ApplyEffectSpecHandleToTarget(AActor* TargetActor, const FGameplayEffectSpecHandle& SpecHandle, EBequestResultType& SuccessType);

	UFUNCTION(BlueprintCallable, Category = "Bequest|Ability")
	void ApplyDamage(FGameplayEventData EventData, TSubclassOf<UGameplayEffect> Effect, bool bIsCharged);
	
	bool SetIsFront(const AActor* QueryActor, const AActor* TargetActor);
	void SendDamage(const FGameplayEventData& EventData, const TSubclassOf<UGameplayEffect>& DamageEffect, const FGameplayAttribute& DamageAttribute, FGameplayTag DamageTypeTag, FGameplayTag DamageEventTag, int32 Multiplier);
	
	UFUNCTION(BlueprintCallable, Category = "Bequest|Ability")
	void SendGameplayEventToActor(AActor* Actor, FGameplayTag EventTag, FGameplayEventData Payload);
	
	UFUNCTION(Server, Reliable)
	void Server_SendGameplayEventToActor(AActor* Actor, FGameplayTag EventTag, FGameplayEventData Payload);
};
