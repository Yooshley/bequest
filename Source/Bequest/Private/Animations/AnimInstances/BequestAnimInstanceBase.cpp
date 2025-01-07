// Copyright Yooshley. All rights reserved.


#include "Animations/AnimInstances/BequestAnimInstanceBase.h"

#include "BequestFunctionLibrary.h"
#include "GameplayTagContainer.h"

bool UBequestAnimInstanceBase::DoesOwnerHaveTag(FGameplayTag Tag) const
{
	if (APawn* OwningPawn = TryGetPawnOwner())
	{
		return UBequestFunctionLibrary::NativeCheckTagOnActor(OwningPawn, Tag);
	}
	return false;
}
