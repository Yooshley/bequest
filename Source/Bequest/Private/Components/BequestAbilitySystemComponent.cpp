// Copyright Yooshley. All rights reserved.


#include "Components/BequestAbilitySystemComponent.h"


UBequestAbilitySystemComponent::UBequestAbilitySystemComponent()
{
	ReplicationMode = EGameplayEffectReplicationMode::Mixed;
	SetIsReplicatedByDefault(true);
}

void UBequestAbilitySystemComponent::InitializeAbilitySystem(AActor* InOwningActor, AActor* InAvatarActor)
{
	if (bIsAbilitySystemInitialized) return;
	bIsAbilitySystemInitialized = true;

	InitAbilityActorInfo(InOwningActor, InAvatarActor);
	if (!AbilitySet.IsEmpty())
	{
		for (const TSubclassOf<UGameplayAbility> GameplayAbility : AbilitySet)
		{
			FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(GameplayAbility, 1, INDEX_NONE, this);
			GiveAbility(AbilitySpec);
		}
	}
}

void UBequestAbilitySystemComponent::GrantAbilities(TArray<TSubclassOf<UGameplayAbility>> Abilities, int32 ApplyLevel)
{
    if (Abilities.IsEmpty()) return;

    for (const auto& Ability : Abilities)
    {
        if (!Ability) continue;

        FGameplayAbilitySpec AbilitySpec(Ability);
        AbilitySpec.SourceObject = GetAvatarActor();
        AbilitySpec.Level = ApplyLevel;

        GiveAbility(AbilitySpec);
    }
}

void UBequestAbilitySystemComponent::RemoveAbilities(TArray<TSubclassOf<UGameplayAbility>> Abilities)
{
	if (Abilities.IsEmpty()) return;
	
	for (const auto& Ability : Abilities)
	{
		if (!Ability) continue;
		
		TArray<FGameplayAbilitySpecHandle> HandlesToRemove;
		for (const FGameplayAbilitySpec& Spec : GetActivatableAbilities())
		{
			if (Spec.Ability && Spec.Ability->GetClass() == Ability)
			{
				HandlesToRemove.Add(Spec.Handle);
			}
		}
		for (const FGameplayAbilitySpecHandle& Handle : HandlesToRemove)
		{
			ClearAbility(Handle);
		}
	}
	for (const auto Ability : AbilitySet)
	{
		if (!Ability) continue;
		
	}
}

bool UBequestAbilitySystemComponent::TryActivateAbilityByTag(FGameplayTag Tag)
{
	check(Tag.IsValid());

	TArray<FGameplayAbilitySpec*> AbilitySpecs;
	GetActivatableGameplayAbilitySpecsByAllMatchingTags(Tag.GetSingleTagContainer(), AbilitySpecs);

	if (!AbilitySpecs.IsEmpty())
	{
		const int32 RandomAbilityIndex = FMath::RandRange(0, AbilitySpecs.Num() - 1);
		const FGameplayAbilitySpec* Spec = AbilitySpecs[RandomAbilityIndex];

		check(Spec);
		if (!Spec->IsActive())
		{
			return TryActivateAbility(Spec->Handle);
		}
	}

	return false;
}
