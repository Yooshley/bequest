// Copyright Yooshley. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "GameFramework/Actor.h"
#include "BequestEquipmentBase.generated.h"

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
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Bequest|Equipment")
	FGameplayTag EquipmentTag;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Bequest|Equipment")
	UStaticMeshComponent* EquipmentMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Bequest|Equipment")
	UBoxComponent* EquipmentCollisionBox;

	UFUNCTION()
	virtual void OnCollisionBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	virtual void OnCollisionBoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

public:
	FORCEINLINE UBoxComponent* GetEquipmentCollisionBox() const { return EquipmentCollisionBox; }
	FORCEINLINE FGameplayTag GetEquipmentTag() const { return EquipmentTag; }
};
