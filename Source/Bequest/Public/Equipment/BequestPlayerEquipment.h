// Copyright Yooshley. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Equipment/BequestEquipmentBase.h"
#include "BequestPlayerEquipment.generated.h"

/**
 * 
 */

struct FGameplayAbilitySpecHandle;
class UBequestPlayerGameplayAbility;

UCLASS()
class BEQUEST_API ABequestPlayerEquipment : public ABequestEquipmentBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<TSubclassOf<UBequestPlayerGameplayAbility>> AbilitySet;
};
