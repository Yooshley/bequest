// Copyright Yooshley. All rights reserved.


#include "Components/BequestAbilitySystemComponent.h"

#include "Data/DataAsset_AbilityData.h"


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
	GrantAbilitiesFromDataAsset(CharacterAbilityData);
}

void UBequestAbilitySystemComponent::GrantAbilitiesFromDataAsset(TSoftObjectPtr<UDataAsset_AbilityData> AbilityData)
{
	if (!AbilityData.IsNull())
	{
		UDataAsset_AbilityData* LoadedData = AbilityData.LoadSynchronous();
		if(LoadedData)
		{
			if (TArray<TSubclassOf<UGameplayAbility>> AbilitySet = LoadedData->GetAbilitySet(); !AbilitySet.IsEmpty())
			{
				for (const TSubclassOf<UGameplayAbility> GameplayAbility : AbilitySet)
				{
					if (FindAbilitySpecFromClass(GameplayAbility)) continue;

					FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(GameplayAbility, 1, INDEX_NONE, this);
					GiveAbility(AbilitySpec);
				}
			}
		}
	}
}

void UBequestAbilitySystemComponent::GrantAbilities(TArray<TSubclassOf<UGameplayAbility>> Abilities, int32 ApplyLevel)
{
    if (Abilities.IsEmpty()) return;

    for (const auto& Ability : Abilities)
    {
        if (!Ability) continue;

    	if (FindAbilitySpecFromClass(Ability))
    	{
    		continue;
    	}
    	
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

		FGameplayAbilitySpec* Spec = FindAbilitySpecFromClass(Ability);
		if (Spec)
		{
			ClearAbility(Spec->Handle);
		}
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
