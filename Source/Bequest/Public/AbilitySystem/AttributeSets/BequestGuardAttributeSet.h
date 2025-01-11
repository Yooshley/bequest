// Copyright Yooshley. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystem/AttributeSets/BequestAttributeSetBase.h"
#include "BequestGuardAttributeSet.generated.h"

/**
 * 
 */
UCLASS()
class BEQUEST_API UBequestGuardAttributeSet : public UBequestAttributeSetBase
{
	GENERATED_BODY()

public:
	UBequestGuardAttributeSet();

	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UPROPERTY(BlueprintReadOnly, Category = "Guard Attribute Set", meta = (HideFromLevelInfos))
	FGameplayAttributeData BaseGuardDamage;
	ATTRIBUTE_ACCESSORS(UBequestGuardAttributeSet, BaseGuardDamage)

	UPROPERTY(BlueprintReadOnly, Category = "Guard Attribute Set", meta = (HideFromLevelInfos))
	FGameplayAttributeData FinalGuardDamage;
	ATTRIBUTE_ACCESSORS(UBequestGuardAttributeSet, FinalGuardDamage)

	UPROPERTY(BlueprintReadOnly, Category = "Guard Attribute Set", meta = (HideFromLevelInfos))
	FGameplayAttributeData Recovery;
	ATTRIBUTE_ACCESSORS(UBequestGuardAttributeSet, Recovery)

	UPROPERTY(BlueprintReadOnly, Category = "Guard Attribute Set", ReplicatedUsing = OnRep_CurrentGuard)
	FGameplayAttributeData CurrentGuard;
	ATTRIBUTE_ACCESSORS(UBequestGuardAttributeSet, CurrentGuard)

	UPROPERTY(BlueprintReadOnly, Category = "Guard Attribute Set", ReplicatedUsing = OnRep_MaximumGuard)
	FGameplayAttributeData MaximumGuard;
	ATTRIBUTE_ACCESSORS(UBequestGuardAttributeSet, MaximumGuard)

	UPROPERTY(BlueprintReadOnly, Category = "Guard Attribute Set", ReplicatedUsing = OnRep_GuardRegeneration)
	FGameplayAttributeData GuardRegeneration;
	ATTRIBUTE_ACCESSORS(UBequestGuardAttributeSet, GuardRegeneration)

protected:
	UFUNCTION()
	virtual void OnRep_CurrentGuard(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	virtual void OnRep_MaximumGuard(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	virtual void OnRep_GuardRegeneration(const FGameplayAttributeData& OldValue);
};
