// Copyright Yooshley. All rights reserved.


#include "AbilitySystem/AttributeSets/BequestLifeAttributeSet.h"

#include "BequestFunctionLibrary.h"
#include "BequestGameplayTags.h"
#include "GameplayEffectExtension.h"
#include "Components/BequestAbilitySystemComponent.h"
#include "Net/UnrealNetwork.h"

UBequestLifeAttributeSet::UBequestLifeAttributeSet()
{
	CurrentLife = 0.f;
	MaximumLife = 0.f;
	BaseLifeDamage = 0.f;
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
	
	if (Data.EvaluatedData.Attribute == GetFinalLifeDamageAttribute())
	{
		const float LocalDamageDone = GetFinalLifeDamage();
		SetFinalLifeDamage(0.f);
		if (LocalDamageDone > 0.0f)
		{
			const float NewLife = GetCurrentLife() - LocalDamageDone;
			SetCurrentLife(FMath::Clamp(NewLife, 0.0f, GetMaximumLife()));
		}
	}
	else if (Data.EvaluatedData.Attribute == GetCurrentLifeAttribute())
	{
		SetCurrentLife(FMath::Clamp(GetCurrentLife(), 0.0f, GetMaximumLife()));
	}

	if (GetCurrentLife() == 0.f)
	{
		//UBequestFunctionLibrary::AddTagWithReferenceCounting(GetOwningActor(), BequestGameplayTags::Character_State_Dead);
		UBequestAbilitySystemComponent* AbilitySystemComponent = Cast<UBequestAbilitySystemComponent>(GetOwningAbilitySystemComponent());
		if (AbilitySystemComponent)
		{
			FGameplayEventData EventData;
			EventData.EventTag = BequestGameplayTags::Character_Event_Death;
			EventData.Instigator = Data.EffectSpec.GetContext().GetInstigator();
			EventData.Target = GetOwningActor();
			AbilitySystemComponent->HandleGameplayEvent(EventData.EventTag, &EventData);
		}
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
