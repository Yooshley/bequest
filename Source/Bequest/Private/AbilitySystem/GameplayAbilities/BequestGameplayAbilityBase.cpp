// Copyright Yooshley. All rights reserved.


#include "AbilitySystem/GameplayAbilities/BequestGameplayAbilityBase.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "BequestGameplayTags.h"
#include "Characters/BequestCharacterBase.h"
#include "Components/BequestAbilitySystemComponent.h"
#include "Components/BequestEquipmentSystemComponent.h"
#include "Types/BequestEnumTypes.h"

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

UBequestEquipmentSystemComponent* UBequestGameplayAbilityBase::GetEquipmentSystemComponent() const
{
	return GetAvatarActorFromActorInfo()->FindComponentByClass<UBequestEquipmentSystemComponent>();
}

UBequestAbilitySystemComponent* UBequestGameplayAbilityBase::GetAbilitySystemComponent() const
{
	return Cast<UBequestAbilitySystemComponent>(CurrentActorInfo->AbilitySystemComponent);
}

FGameplayEffectSpecHandle UBequestGameplayAbilityBase::GetDamageEffectSpecHandle(TSubclassOf<UGameplayEffect> Effect,
	float Damage, FGameplayTag TypeTag)
{
	check(Effect);
	
	FGameplayEffectContextHandle EffectContextHandle = GetAbilitySystemComponent()->MakeEffectContext();
	EffectContextHandle.SetAbility(this);
	EffectContextHandle.AddSourceObject(GetAvatarActorFromActorInfo());
	EffectContextHandle.AddInstigator(GetAvatarActorFromActorInfo(), GetAvatarActorFromActorInfo());
	
	FGameplayEffectSpecHandle EffectSpecHandle = GetAbilitySystemComponent()->MakeOutgoingSpec(Effect, GetAbilityLevel(), EffectContextHandle);
	EffectSpecHandle.Data->SetSetByCallerMagnitude(TypeTag, Damage);
	
	return EffectSpecHandle;
}

FActiveGameplayEffectHandle UBequestGameplayAbilityBase::NativeApplyEffectSpecHandleToTarget(AActor* TargetActor,
                                                                                             const FGameplayEffectSpecHandle& SpecHandle)
{
	UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
	check(TargetASC && SpecHandle.IsValid());
	
	return GetAbilitySystemComponent()->ApplyGameplayEffectSpecToTarget(*SpecHandle.Data,TargetASC);
}

FActiveGameplayEffectHandle UBequestGameplayAbilityBase::ApplyEffectSpecHandleToTarget(AActor* TargetActor,
	const FGameplayEffectSpecHandle& SpecHandle, EBequestResultType& SuccessType)
{
	FActiveGameplayEffectHandle ActiveGameplayEffectHandle = NativeApplyEffectSpecHandleToTarget(TargetActor, SpecHandle);
	SuccessType = ActiveGameplayEffectHandle.WasSuccessfullyApplied() ? EBequestResultType::Success : EBequestResultType::Failure;
	return ActiveGameplayEffectHandle;
}

void UBequestGameplayAbilityBase::SendGameplayEventToActor(AActor* Actor, FGameplayTag EventTag,
	FGameplayEventData Payload)
{
	if (IsLocallyControlled())
	{
		UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(Actor, EventTag, Payload);
	}
	else
	{
		Server_SendGameplayEventToActor(Actor, EventTag, Payload);
	}
}

void UBequestGameplayAbilityBase::Server_SendGameplayEventToActor_Implementation(AActor* Actor, FGameplayTag EventTag, FGameplayEventData Payload)
{
	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(Actor, EventTag, Payload);
}
