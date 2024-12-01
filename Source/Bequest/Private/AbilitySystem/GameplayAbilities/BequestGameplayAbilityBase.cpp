// Copyright Yooshley. All rights reserved.


#include "AbilitySystem/GameplayAbilities/BequestGameplayAbilityBase.h"

#include "Characters/BequestCharacterBase.h"
#include "Components/BequestAbilitySystemComponent.h"

UBequestGameplayAbilityBase::UBequestGameplayAbilityBase()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;	
}

void UBequestGameplayAbilityBase::OnAvatarSet(const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilitySpec& Spec)
{
	Super::OnAvatarSet(ActorInfo, Spec);
	
	QuestCharacter = Cast<ABequestCharacterBase>(ActorInfo->AvatarActor);
	
	if (bActivateAbilityOnGrant)
	{
		QuestCharacter->GetBequestAbilitySystemComponent()->TryActivateAbility(Spec.Handle);
	}
}
