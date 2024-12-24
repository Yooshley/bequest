// Copyright Yooshley. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Components/PawnExtenstionComponentBase.h"
#include "Equipment/BequestEquipmentBase.h"
#include "BequestEquipmentSystemComponent.generated.h"

class ABequestEquipmentBase;

/**
 * 
 */
UCLASS()
class BEQUEST_API UBequestEquipmentSystemComponent : public UPawnExtenstionComponentBase
{
	GENERATED_BODY()

public:
	UBequestEquipmentSystemComponent();

	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;
	
	UFUNCTION(BlueprintCallable, Category = "Bequest|EquipmentSystem")
	void RegisterEquipment(ABequestEquipmentBase* Equipment, bool bRegisterEquipped = false);

	UFUNCTION(BlueprintCallable, Category = "Bequest|EquipmentSystem")
	ABequestEquipmentBase* GetCarriedEquipmentByTag(FGameplayTag EquipmentTag) const;

	UFUNCTION(BlueprintCallable, Category = "Bequest|EquipmentSystem")
	ABequestEquipmentBase* GetEquippedEquipment() const;

	UFUNCTION(BlueprintCallable, Category = "Bequest|EquipmentSystem")
	void ToggleEquipmentCollision(bool bShouldEnable);

	virtual void OnEquipmentHitTargetActorBegin(AActor* HitActor);
	virtual void OnEquipmentHitTargetActorEnd(AActor* HitActor);

	UPROPERTY(Replicated, BlueprintReadWrite, Category = "Bequest|EquipmentSystem")
	TArray<ABequestEquipmentBase*> CarriedEquipment;
	
	UPROPERTY(Replicated, BlueprintReadWrite, Category = "Bequest|EquipmentSystem")
	FGameplayTag EquippedEquipmentTag;

	UPROPERTY(BlueprintReadWrite, Category = "Bequest|EquipmentSystem")
	int32 MontageIndex = 1;

	UFUNCTION(BlueprintCallable, Category = "Bequest|EquipmentSystem")
	void IncrementMontage();

	UFUNCTION(BlueprintCallable, Category = "Bequest|EquipmentSystem")
	UAnimMontage* GetEquipmentMontage();
	
	UFUNCTION(BlueprintCallable, Category = "Bequest|EquipmentSystem")
	TSubclassOf<UBequestCharacterLinkedAnimLayer> GetEquipmentAnimLayer();

protected:
	TArray<AActor*> EquipmentOverlappedActors;
};
