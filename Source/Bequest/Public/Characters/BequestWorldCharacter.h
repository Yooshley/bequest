// Copyright Yooshley. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Characters/BequestCharacterBase.h"
#include "BequestWorldCharacter.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class BEQUEST_API ABequestWorldCharacter : public ABequestCharacterBase
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
	virtual void PostNetReceive() override;
};
