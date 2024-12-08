// Copyright Yooshley. All rights reserved.


#include "AbilitySystem/AbilityTasks/AbilityTask_WaitInputEvent.h"

#include "EnhancedInputComponent.h"

UAbilityTask_WaitInputEvent* UAbilityTask_WaitInputEvent::WaitInputEvent(UGameplayAbility* OwningAbility, const FName TaskInstanceName, UInputAction* InputAction, const ETriggerEvent TriggerEventType, bool bShouldOnlyTriggerOnce)
{
	UAbilityTask_WaitInputEvent* AbilityTask = NewAbilityTask<UAbilityTask_WaitInputEvent>(OwningAbility, TaskInstanceName);
	
	AbilityTask->InputAction = InputAction;
	AbilityTask->EventType = TriggerEventType;
	AbilityTask->bTriggerOnce = bShouldOnlyTriggerOnce;
	
	return AbilityTask;
}

void UAbilityTask_WaitInputEvent::Activate()
{
	Super::Activate();

	if (!AbilitySystemComponent.Get() || !Ability || !InputAction.IsValid())
	{
		return;
	}

	if (const APawn* AvatarPawn = Cast<APawn>(Ability->GetAvatarActorFromActorInfo()))
	{
		if (const APlayerController* PlayerController = Cast<APlayerController>(AvatarPawn->GetController()))
		{
			EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerController->InputComponent);
			
			if (IsValid(EnhancedInputComponent.Get()))
			{
				EnhancedInputComponent->BindAction(InputAction.Get(), EventType, this, &UAbilityTask_WaitInputEvent::EventReceived);
			}
		}
	}
}

void UAbilityTask_WaitInputEvent::EventReceived(const FInputActionValue& Value)
{
	if (bTriggerOnce && bHasBeenTriggered)
	{
		return;
	}

	bHasBeenTriggered = true;
	
	InputEventReceived.Broadcast(Value);
}

void UAbilityTask_WaitInputEvent::OnDestroy(const bool bInOwnerFinished)
{
	if (IsValid(EnhancedInputComponent.Get()))
	{
		EnhancedInputComponent->ClearBindingsForObject(this);
	}
	Super::OnDestroy(bInOwnerFinished);
}