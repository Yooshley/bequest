// Copyright Yooshley. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystem/AttributeSets/BequestAttributeSetBase.h"
#include "BequestArmorAttributeSet.generated.h"

/**
 * 
 */
UCLASS()
class BEQUEST_API UBequestArmorAttributeSet : public UBequestAttributeSetBase
{
	GENERATED_BODY()

public:
	UBequestArmorAttributeSet();

	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UPROPERTY(BlueprintReadOnly, Category = "Armor Attribute Set", meta = (HideFromLevelInfos))
	FGameplayAttributeData Damage;
	ATTRIBUTE_ACCESSORS(UBequestArmorAttributeSet, Damage)

	UPROPERTY(BlueprintReadOnly, Category = "Armor Attribute Set", ReplicatedUsing = OnRep_CurrentArmor)
	FGameplayAttributeData CurrentArmor;
	ATTRIBUTE_ACCESSORS(UBequestArmorAttributeSet, CurrentArmor)

	UPROPERTY(BlueprintReadOnly, Category = "Armor Attribute Set", ReplicatedUsing = OnRep_MaximumArmor)
	FGameplayAttributeData MaximumArmor;
	ATTRIBUTE_ACCESSORS(UBequestArmorAttributeSet, MaximumArmor)

protected:
	UFUNCTION()
	virtual void OnRep_CurrentArmor(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	virtual void OnRep_MaximumArmor(const FGameplayAttributeData& OldValue);
};
