// Copyright Yooshley. All rights reserved.


#include "AbilitySystem/AttributeSets/BequestArmorAttributeSet.h"

#include "AbilitySystemComponent.h"
#include "GameplayEffectExtension.h"
#include "GameplayEffectTypes.h"
#include "Net/UnrealNetwork.h"

UBequestArmorAttributeSet::UBequestArmorAttributeSet()
{
	MaximumArmor = 0.f;
	CurrentArmor = 0.f;
}

void UBequestArmorAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);

	if (Attribute == GetMaximumArmorAttribute())
	{
		AdjustAttributeForMaxChange(CurrentArmor, MaximumArmor, NewValue, GetCurrentArmorAttribute());
	}
}

void UBequestArmorAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	if (Data.EvaluatedData.Attribute == GetDamageAttribute())
	{
		const float LocalDamageDone = GetDamage();
		SetDamage(0.f);
		if (LocalDamageDone > 0.0f)
		{
			const float NewHealth = GetCurrentArmor() - LocalDamageDone;
			SetCurrentArmor(FMath::Clamp(NewHealth, 0.0f, GetMaximumArmor()));
		}
	}
	
	else if (Data.EvaluatedData.Attribute == GetCurrentArmorAttribute())
	{
		SetCurrentArmor(FMath::Clamp(GetCurrentArmor(), 0.0f, GetMaximumArmor()));
	}
}

void UBequestArmorAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UBequestArmorAttributeSet, CurrentArmor, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UBequestArmorAttributeSet, MaximumArmor, COND_None, REPNOTIFY_Always);
}

void UBequestArmorAttributeSet::OnRep_CurrentArmor(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UBequestArmorAttributeSet, CurrentArmor, OldValue);
}

void UBequestArmorAttributeSet::OnRep_MaximumArmor(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UBequestArmorAttributeSet, MaximumArmor, OldValue);
}
