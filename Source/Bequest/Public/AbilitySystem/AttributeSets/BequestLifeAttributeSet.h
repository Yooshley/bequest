// Copyright Yooshley. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystem/AttributeSets/BequestAttributeSetBase.h"
#include "BequestLifeAttributeSet.generated.h"

/**
 * 
 */
UCLASS()
class BEQUEST_API UBequestLifeAttributeSet : public UBequestAttributeSetBase
{
	GENERATED_BODY()

public:
	UBequestLifeAttributeSet();

	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UPROPERTY(BlueprintReadOnly, Category = "Life Attribute Set", meta = (HideFromLevelInfos))
	FGameplayAttributeData LifeDamage;
	ATTRIBUTE_ACCESSORS(UBequestLifeAttributeSet, LifeDamage)

	UPROPERTY(BlueprintReadOnly, Category = "Life Attribute Set", ReplicatedUsing = OnRep_CurrentLife)
	FGameplayAttributeData CurrentLife;
	ATTRIBUTE_ACCESSORS(UBequestLifeAttributeSet, CurrentLife)

	UPROPERTY(BlueprintReadOnly, Category = "Life Attribute Set", ReplicatedUsing = OnRep_MaximumLife)
	FGameplayAttributeData MaximumLife;
	ATTRIBUTE_ACCESSORS(UBequestLifeAttributeSet, MaximumLife)

protected:
	UFUNCTION()
	virtual void OnRep_CurrentLife(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	virtual void OnRep_MaximumLife(const FGameplayAttributeData& OldValue);
	
};
