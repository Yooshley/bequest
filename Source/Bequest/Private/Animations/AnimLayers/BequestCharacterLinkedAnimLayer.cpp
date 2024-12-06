// Copyright Yooshley. All rights reserved.


#include "Animations/AnimLayers/BequestCharacterLinkedAnimLayer.h"

#include "Animations/AnimInstances/BequestCharacterAnimInstance.h"

UBequestCharacterAnimInstance* UBequestCharacterLinkedAnimLayer::GetCharacterAnimInstance() const
{
	return Cast<UBequestCharacterAnimInstance>(GetOwningComponent()->GetAnimInstance());
}
