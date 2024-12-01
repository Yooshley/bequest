// Copyright Yooshley. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Animations/AnimInstances/BequestAnimInstanceBase.h"
#include "BequestCharacterAnimInstance.generated.h"

class UCharacterMovementComponent;
class ABequestCharacterBase;
/**
 * 
 */
UCLASS()
class BEQUEST_API UBequestCharacterAnimInstance : public UBequestAnimInstanceBase
{
	GENERATED_BODY()

public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeThreadSafeUpdateAnimation(float DeltaSeconds) override;

protected:
	UPROPERTY()
	ABequestCharacterBase* OwningCharacter;
	
	UPROPERTY()
	UCharacterMovementComponent* OwningMovementComponent;
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Bequest|Locomotion")
	float GroundSpeed;
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Bequest|Locomotion")
	bool bHasAcceleration;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Bequest|Locomotion")
	float LocomotionDirection;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Bequest|Equipment")
	bool bHasEquipment;
};
