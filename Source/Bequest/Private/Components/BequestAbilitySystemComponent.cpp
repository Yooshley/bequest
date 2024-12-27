// Copyright Yooshley. All rights reserved.


#include "Components/BequestAbilitySystemComponent.h"

#include "Data/AttributeSetDataTableRow.h"
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
	LoadAbilityData(AbilitySystemData, AttributeDataTable);
}

void UBequestAbilitySystemComponent::LoadAbilityData(TSoftObjectPtr<UDataAsset_AbilitySystem> InAbilityDataAsset, UDataTable* InAttributeDataTable)
{
	if (GetOwnerActor()->HasAuthority())
	{
		if (InAbilityDataAsset.IsNull()) return;
		UDataAsset_AbilitySystem* LoadedData = InAbilityDataAsset.LoadSynchronous();
		if(LoadedData)
		{
			if (TArray<TSubclassOf<UAttributeSet>> Attributes = LoadedData->GetAttributes(); !Attributes.IsEmpty())
			{
				for (const TSubclassOf<UAttributeSet> AttributeSetClass : Attributes)
				{
					GetOrCreateAttributeSet(AttributeSetClass);
				}
			}

			checkf(InAttributeDataTable, TEXT("Attribute Data Table not assigned."));
			TArray<FName> RowNames = InAttributeDataTable->GetRowNames();
			for (const FName& RowName : RowNames)
			{
				FAttributeSetDataTableRow* Row = InAttributeDataTable->FindRow<FAttributeSetDataTableRow>(RowName, TEXT("AttributeSetup"));
				if (Row)
				{
					FGameplayAttribute Attribute = Row->Attribute;
					float AttributeValue = Row->AttributeValue;

					if (HasAttributeSetForAttribute(Attribute))
					{
						SetNumericAttributeBase(Attribute, AttributeValue);
					}
				}
			}
		
			if (TArray<TSubclassOf<UGameplayAbility>> Abilities = LoadedData->GetAbilities(); !Abilities.IsEmpty())
			{
				for (const TSubclassOf<UGameplayAbility> GameplayAbilityClass : Abilities)
				{
					if (FindAbilitySpecFromClass(GameplayAbilityClass)) continue;

					FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(GameplayAbilityClass, 1, INDEX_NONE, this);
					GiveAbility(AbilitySpec);
				}
			}
			
			if (TArray<TSubclassOf<UGameplayEffect>> Effects = LoadedData->GetEffects(); !Effects.IsEmpty())
            {
            	for (const TSubclassOf<UGameplayEffect>& GameplayEffectClass : Effects)
            	{
            		if (!IsValid(GameplayEffectClass)) continue;
            		FGameplayEffectContextHandle EffectContextHandle = MakeEffectContext();
            		EffectContextHandle.AddSourceObject(this);
            		if (FGameplayEffectSpecHandle GameplayEffectSpecHandle = MakeOutgoingSpec(GameplayEffectClass, 1, EffectContextHandle); GameplayEffectSpecHandle.IsValid())
            		{
            			ApplyGameplayEffectSpecToTarget(*GameplayEffectSpecHandle.Data.Get(), this);
            		}
            	}
            }
		}
	}
}

const UAttributeSet* UBequestAbilitySystemComponent::GetOrCreateAttributeSet(const TSubclassOf<UAttributeSet>& AttributeSet)
{
	return GetOrCreateAttributeSubobject(AttributeSet);
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
