// Copyright Yooshley. All rights reserved.

#pragma once
#include "GameplayTagContainer.h"

#include "BequestStructTypes.generated.h"

class UDataAsset_AbilityData;
class UBequestCharacterLinkedAnimLayer;

USTRUCT(BlueprintType)
struct FBequestEquipmentData
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FGameplayTag EquipmentTag;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UBequestCharacterLinkedAnimLayer> EquipmentAnimLayerToLink;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSoftObjectPtr<UDataAsset_AbilityData> EquipmentAbilityData;
};