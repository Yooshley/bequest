// Copyright Yooshley. All rights reserved.


#include "AbilitySystem/GameplayAbilities/BequestGameplayAbilityBase.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "BequestDebugHelper.h"
#include "BequestFunctionLibrary.h"
#include "BequestGameplayTags.h"
#include "AbilitySystem/AttributeSets/BequestArmorAttributeSet.h"
#include "AbilitySystem/AttributeSets/BequestGuardAttributeSet.h"
#include "AbilitySystem/AttributeSets/BequestLifeAttributeSet.h"
#include "Characters/BequestCharacterBase.h"
#include "Components/BequestAbilitySystemComponent.h"
#include "Components/BequestEquipmentSystemComponent.h"
#include "Kismet/KismetMathLibrary.h"
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

void UBequestGameplayAbilityBase::ApplyDamage(FGameplayEventData EventData, TSubclassOf<UGameplayEffect> Effect, bool bIsCharged)
{
	const AActor* TargetActorConst = EventData.Target;
	AActor* TargetActor = const_cast<AActor*>(TargetActorConst);
	UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);

	const AActor* InstigatorActor = EventData.Instigator;
	
	if (UBequestFunctionLibrary::NativeCheckTagOnActor(TargetActor, BequestGameplayTags::Character_State_Invulnerable)) return;

	const int32 Multiplier = bIsCharged ? 2 : 1;
	const bool bIsFront = SetIsFront(InstigatorActor, TargetActorConst);

	bool bSuccessfullyFoundAttribute;
	const float TargetGuardAttributeValue = UAbilitySystemBlueprintLibrary::GetFloatAttributeFromAbilitySystemComponent(TargetASC, UBequestGuardAttributeSet::GetCurrentGuardAttribute(), bSuccessfullyFoundAttribute);
	const float TargetArmorAttributeValue = UAbilitySystemBlueprintLibrary::GetFloatAttributeFromAbilitySystemComponent(TargetASC, UBequestArmorAttributeSet::GetCurrentArmorAttribute(), bSuccessfullyFoundAttribute);
	
	FGameplayAttribute DamageAttribute;
	FGameplayTag DamageTypeTag;
	FGameplayTag DamageEventTag;
	
	if (UBequestFunctionLibrary::NativeCheckTagOnActor(TargetActor, BequestGameplayTags::Character_State_Guarded) && bIsFront && TargetGuardAttributeValue > 0)
	{
		DamageAttribute = UBequestGuardAttributeSet::GetBaseGuardDamageAttribute();
		DamageTypeTag = BequestGameplayTags::Character_SetByCaller_Damage_Guard;
		DamageEventTag = BequestGameplayTags::Character_Event_Block;
	}
	else if (UBequestFunctionLibrary::NativeCheckTagOnActor(TargetActor, BequestGameplayTags::Character_State_Armored) && TargetArmorAttributeValue > 0)
	{
		DamageAttribute = UBequestArmorAttributeSet::GetBaseArmorDamageAttribute();
		DamageTypeTag = BequestGameplayTags::Character_SetByCaller_Damage_Armor;
		DamageEventTag = BequestGameplayTags::Character_Event_Absorb;
	}
	else
	{
		DamageAttribute = UBequestLifeAttributeSet::GetBaseLifeDamageAttribute();
		DamageTypeTag = BequestGameplayTags::Character_SetByCaller_Damage_Life;
		if (Multiplier > 1)
		{
			DamageEventTag = BequestGameplayTags::Character_Event_Hurt_Heavy;
		}
		else
		{
			DamageEventTag = BequestGameplayTags::Character_Event_Hurt;
		}
	}
	SendDamage(EventData, Effect, DamageAttribute, DamageTypeTag, DamageEventTag, Multiplier);
}

bool UBequestGameplayAbilityBase::SetIsFront(const AActor* QueryActor, const AActor* TargetActor)
{
	const FVector QueryActorLocation = QueryActor->GetActorLocation();
	const FVector TargetActorLocation = TargetActor->GetActorLocation();
	const FVector NormalVector = UKismetMathLibrary::Normal(QueryActorLocation - TargetActorLocation);
	const float DotProduct = FVector::DotProduct(NormalVector, TargetActor->GetActorForwardVector());
	return  DotProduct > 0.f;
}

void UBequestGameplayAbilityBase::SendDamage(const FGameplayEventData& EventData, const TSubclassOf<UGameplayEffect>& DamageEffect, const FGameplayAttribute& DamageAttribute, const FGameplayTag DamageTypeTag, const FGameplayTag DamageEventTag, const int32 Multiplier)
{
	const AActor* InstigatorActorConst = EventData.Instigator;
	AActor* InstigatorActor = const_cast<AActor*>(InstigatorActorConst);
	APawn* InstigatorPawn = Cast<APawn>(InstigatorActor);
	
	const AActor* TargetActorConst = EventData.Target;
	AActor* TargetActor = const_cast<AActor*>(TargetActorConst);
	APawn* TargetPawn = Cast<APawn>(TargetActor);

	bool bSuccessfullyFoundAttribute;
	const float AttributeValue = UAbilitySystemBlueprintLibrary::GetFloatAttributeFromAbilitySystemComponent(GetAbilitySystemComponent(), DamageAttribute, bSuccessfullyFoundAttribute);
	if (bSuccessfullyFoundAttribute)
	{
		float Damage = 0;
		if (UBequestFunctionLibrary::NativeCheckTagOnActor(TargetActor, BequestGameplayTags::Character_State_Deflect))
		{
			UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(TargetActor, BequestGameplayTags::Character_Event_Block, EventData);
			return;
		}
		if (UBequestFunctionLibrary::IsTargetPawnHostile(InstigatorPawn, TargetPawn))
		{
			Damage = AttributeValue * Multiplier;
			BequestDebug::Print(TEXT("Damage"), Damage);
			BequestDebug::Print(TEXT("Multiplier"), Multiplier);
		}
	
		UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(TargetActor, DamageEventTag, EventData);
		NativeApplyEffectSpecHandleToTarget(TargetActor, GetDamageEffectSpecHandle(DamageEffect, Damage, DamageTypeTag));
	}
}

void UBequestGameplayAbilityBase::SendGameplayEventToActor(AActor* Actor, FGameplayTag EventTag, FGameplayEventData Payload)
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
