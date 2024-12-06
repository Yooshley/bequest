// Copyright Yooshley. All rights reserved.


#include "AbilitySystem/GameplayAbilities/BequestPlayerGameplayAbility.h"

#include "EnhancedInputComponent.h"
#include "Characters/BequestPlayerCharacter.h"
#include "Components/BequestAbilitySystemComponent.h"



void UBequestPlayerGameplayAbility::OnAvatarSet(const FGameplayAbilityActorInfo* ActorInfo,
                                                const FGameplayAbilitySpec& Spec)
{
	Super::OnAvatarSet(ActorInfo, Spec);
	QuestPlayerCharacter = Cast<ABequestPlayerCharacter>(ActorInfo->AvatarActor);
	SetupEnhancedInputBindings(ActorInfo, Spec);
}

void UBequestPlayerGameplayAbility::SetupEnhancedInputBindings(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(QuestPlayerCharacter->GetController()->InputComponent.Get()))
	{
		if (ActivationInputAction)
		{
			if (InputPressedTriggerType != ETriggerEvent::None)
			{
				EnhancedInputComponent->BindAction(ActivationInputAction, InputPressedTriggerType, this, &ThisClass::HandleInputPressedEvent, Spec.Handle);
			}
			if (InputReleasedTriggerType != ETriggerEvent::None)
			{
				EnhancedInputComponent->BindAction(ActivationInputAction, InputReleasedTriggerType, this, &ThisClass::HandleInputReleasedEvent, Spec.Handle);
			}
		}
	}
}

void UBequestPlayerGameplayAbility::HandleInputPressedEvent(const FInputActionValue& InputValue, const FGameplayAbilitySpecHandle SpecHandle)
{
	UAbilitySystemComponent* AbilitySystemComponent = QuestPlayerCharacter->GetBequestAbilitySystemComponent();
	FGameplayAbilitySpec* Spec = AbilitySystemComponent->FindAbilitySpecFromHandle(SpecHandle);
	if (Spec)
	{
		Spec->InputPressed = true;
		
		if (ActivationInputAction)
		{
			CachedInputActionValue = InputValue;
		}
		
		if (Spec->IsActive())
		{
			if (Spec->Ability.Get()->bReplicateInputDirectly && AbilitySystemComponent->IsOwnerActorAuthoritative() == false)
			{
				AbilitySystemComponent->ServerSetInputPressed(Spec->Ability.Get()->GetCurrentAbilitySpecHandle());
			}
			AbilitySystemComponent->AbilitySpecInputPressed(*Spec);
			AbilitySystemComponent->InvokeReplicatedEvent(EAbilityGenericReplicatedEvent::InputPressed, Spec->Handle, GetCurrentActivationInfo().GetActivationPredictionKey());
		}
		else
		{
			AbilitySystemComponent->TryActivateAbility(SpecHandle);
		}
	}
}

void UBequestPlayerGameplayAbility::HandleInputReleasedEvent(const FGameplayAbilitySpecHandle SpecHandle)
{
	UAbilitySystemComponent* AbilitySystemComponent = QuestPlayerCharacter->GetBequestAbilitySystemComponent();
	FGameplayAbilitySpec* Spec = AbilitySystemComponent->FindAbilitySpecFromHandle(SpecHandle);
	if (Spec)
	{
		Spec->InputPressed = false;
		
		if (ActivationInputAction)
		{
			CachedInputActionValue = FInputActionValue();
		}
		
		if (Spec->IsActive())
		{
			if (Spec->Ability.Get()->bReplicateInputDirectly && AbilitySystemComponent->IsOwnerActorAuthoritative() == false)
			{
				AbilitySystemComponent->ServerSetInputReleased(Spec->Ability.Get()->GetCurrentAbilitySpecHandle());
			}
			AbilitySystemComponent->AbilitySpecInputReleased(*Spec);
			AbilitySystemComponent->InvokeReplicatedEvent(EAbilityGenericReplicatedEvent::InputReleased, Spec->Handle, GetCurrentActivationInfo().GetActivationPredictionKey());
		}
	}
}

void UBequestPlayerGameplayAbility::OnRemoveAbility(const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilitySpec& Spec)
{
	if (!QuestPlayerCharacter.IsValid() || !QuestPlayerCharacter->GetController())
	{
		return;
	}
	
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(QuestPlayerCharacter->GetController()->InputComponent.Get()))
	{
		EnhancedInputComponent->ClearBindingsForObject(Spec.Ability.Get());
	}
	Super::OnRemoveAbility(ActorInfo, Spec);
}
