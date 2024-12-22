// Copyright Yooshley. All rights reserved.


#include "AbilitySystem/AttributeSets/BequestGuardAttributeSet.h"
#include "GameplayEffectExtension.h"
#include "Net/UnrealNetwork.h"

UBequestGuardAttributeSet::UBequestGuardAttributeSet()
{
	MaximumGuard = 0.f;
	CurrentGuard = 0.f;
	GuardRegeneration = 0.f;
}

void UBequestGuardAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);

	if (Attribute == GetMaximumGuardAttribute())
	{
		AdjustAttributeForMaxChange(CurrentGuard, MaximumGuard, NewValue, GetCurrentGuardAttribute());
	}
}

void UBequestGuardAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	if (Data.EvaluatedData.Attribute == GetDamageAttribute())
	{
		const float LocalDamageDone = GetDamage();
		SetDamage(0.f);
		if (LocalDamageDone > 0.0f)
		{
			const float NewHealth = GetCurrentGuard() - LocalDamageDone;
			SetCurrentGuard(FMath::Clamp(NewHealth, 0.0f, GetMaximumGuard()));
		}
	}

	else if (Data.EvaluatedData.Attribute == GetRecoveryAttribute())
	{
		const float LocalHealingDone = GetRecovery();
		SetRecovery(0.f);
		if (LocalHealingDone > 0.0f)
		{
			const float NewHealth = GetCurrentGuard() + LocalHealingDone;
			SetCurrentGuard(FMath::Clamp(NewHealth, 0.0f, GetMaximumGuard()));
		}
	}
	
	else if (Data.EvaluatedData.Attribute == GetCurrentGuardAttribute())
	{
		SetCurrentGuard(FMath::Clamp(GetCurrentGuard(), 0.0f, GetMaximumGuard()));
	}

	else if (Data.EvaluatedData.Attribute == GetGuardRegenerationAttribute())
	{
		SetGuardRegeneration(FMath::Clamp(GetGuardRegeneration(), 0.0f, GetMaximumGuard()));
	}
}

void UBequestGuardAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UBequestGuardAttributeSet, CurrentGuard, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UBequestGuardAttributeSet, MaximumGuard, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UBequestGuardAttributeSet, GuardRegeneration, COND_None, REPNOTIFY_Always);
}

void UBequestGuardAttributeSet::OnRep_CurrentGuard(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UBequestGuardAttributeSet, CurrentGuard, OldValue);
}

void UBequestGuardAttributeSet::OnRep_MaximumGuard(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UBequestGuardAttributeSet, MaximumGuard, OldValue);
}

void UBequestGuardAttributeSet::OnRep_GuardRegeneration(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UBequestGuardAttributeSet, GuardRegeneration, OldValue);
}

