// Copyright Yooshley. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "GameFramework/Actor.h"
#include "BequestEquipmentBase.generated.h"

class UDataAsset_AbilityData;
class UBoxComponent;

DECLARE_DELEGATE_OneParam(FOnTargetHitDelegate, AActor*)

UCLASS()
class BEQUEST_API ABequestEquipmentBase : public AActor
{
	GENERATED_BODY()
	
public:	
	ABequestEquipmentBase();
	
	FOnTargetHitDelegate OnEquipmentHitTargetBegin;
	FOnTargetHitDelegate OnEquipmentHitTargetEnd;
	
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Bequest|EquipmentSystem")
	FGameplayTag EquipmentTag;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Bequest|EquipmentSystem")
	UStaticMeshComponent* EquipmentMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Bequest|EquipmentSystem")
	UBoxComponent* EquipmentCollisionBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Bequest|EquipmentSystem")
	TSoftObjectPtr<UDataAsset_AbilityData> EquipmentAbilityData;

	UFUNCTION()
	virtual void OnCollisionBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	virtual void OnCollisionBoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

public:
	FORCEINLINE UBoxComponent* GetEquipmentCollisionBox() const { return EquipmentCollisionBox; }
	FORCEINLINE FGameplayTag GetEquipmentTag() const { return EquipmentTag; }
	FORCEINLINE TSoftObjectPtr<UDataAsset_AbilityData> GetEquipmentAbilityData() const { return EquipmentAbilityData; }
};
