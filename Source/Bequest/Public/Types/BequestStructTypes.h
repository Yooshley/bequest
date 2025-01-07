// Copyright Yooshley. All rights reserved.

#pragma once
#include "GameplayTagContainer.h"

#include "BequestStructTypes.generated.h"

class UDataAsset_AbilitySystem;
class UBequestCharacterLinkedAnimLayer;

USTRUCT(BlueprintType)
struct FBequestEquipmentData
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FGameplayTag EquipmentTag;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UBequestCharacterLinkedAnimLayer> EquipmentAnimLayerToLink;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TMap<int32, UAnimMontage*> EquipmentMontageMap;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TMap<int32, UAnimMontage*> EquipmentAlternateMontageMap;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSoftObjectPtr<UDataAsset_AbilitySystem> EquipmentPlayerAbilityData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSoftObjectPtr<UDataAsset_AbilitySystem> EquipmentWorldAbilityData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UDataTable* EquipmentAttributeDataTable;
};