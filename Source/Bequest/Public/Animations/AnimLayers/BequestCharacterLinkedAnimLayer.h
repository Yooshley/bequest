// Copyright Yooshley. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Animations/AnimInstances/BequestAnimInstanceBase.h"
#include "BequestCharacterLinkedAnimLayer.generated.h"

class UBequestCharacterAnimInstance;
/**
 * 
 */
UCLASS()
class BEQUEST_API UBequestCharacterLinkedAnimLayer : public UBequestAnimInstanceBase
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure, meta = (NotBlueprintThreadSafe))
	UBequestCharacterAnimInstance* GetCharacterAnimInstance() const;
};
