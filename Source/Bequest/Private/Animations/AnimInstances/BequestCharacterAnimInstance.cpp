// Copyright Yooshley. All rights reserved.


#include "Animations/AnimInstances/BequestCharacterAnimInstance.h"

#include "Characters/BequestCharacterBase.h"
#include "Components/BequestEquipmentSystemComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Runtime/AnimGraphRuntime/Public/KismetAnimationLibrary.h"

void UBequestCharacterAnimInstance::NativeInitializeAnimation()
{
	OwningCharacter = Cast<ABequestCharacterBase>(TryGetPawnOwner());
	if (OwningCharacter)
	{
		OwningMovementComponent = OwningCharacter->GetCharacterMovement();
	}
}

void UBequestCharacterAnimInstance::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
	if (!OwningCharacter || !OwningMovementComponent)
	{
		return;
	}
	GroundSpeed = OwningCharacter->GetVelocity().Size2D();
	bHasAcceleration = OwningMovementComponent->GetCurrentAcceleration().SizeSquared2D()>0.f;
	
	LocomotionDirection = UKismetAnimationLibrary::CalculateDirection(OwningCharacter->GetVelocity(), OwningCharacter->GetActorRotation());

	EquippedEquipmentTag = OwningCharacter->GetBequestEquipmentSystemComponent()->EquippedEquipmentTag;
}
