// Copyright Yooshley. All rights reserved.


#include "AbilitySystem/AttributeSets/BequestLifeAttributeSet.h"

#include "GameplayEffectExtension.h"
#include "Net/UnrealNetwork.h"

UBequestLifeAttributeSet::UBequestLifeAttributeSet()
{
	CurrentLife = 0.f;
	MaximumLife = 0.f;
}

void UBequestLifeAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);

	if (Attribute == GetMaximumLifeAttribute())
	{
		AdjustAttributeForMaxChange(CurrentLife, MaximumLife, NewValue, GetCurrentLifeAttribute());
	}
}

void UBequestLifeAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);
	
	if (Data.EvaluatedData.Attribute == GetDamageAttribute())
	{
		const float LocalDamageDone = GetDamage();
		SetDamage(0.f);
		if (LocalDamageDone > 0.0f)
		{
			const float NewHealth = GetCurrentLife() - LocalDamageDone;
			SetCurrentLife(FMath::Clamp(NewHealth, 0.0f, GetMaximumLife()));
		}
	}
	
	else if (Data.EvaluatedData.Attribute == GetCurrentLifeAttribute())
	{
		SetCurrentLife(FMath::Clamp(GetCurrentLife(), 0.0f, GetMaximumLife()));
	}
}

void UBequestLifeAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UBequestLifeAttributeSet, CurrentLife, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UBequestLifeAttributeSet, MaximumLife, COND_None, REPNOTIFY_Always);
}

void UBequestLifeAttributeSet::OnRep_CurrentLife(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UBequestLifeAttributeSet, CurrentLife, OldValue);
}

void UBequestLifeAttributeSet::OnRep_MaximumLife(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UBequestLifeAttributeSet, MaximumLife, OldValue);
}
