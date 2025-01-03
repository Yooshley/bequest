// Copyright Yooshley. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Types/BequestStructTypes.h"
#include "NiagaraComponent.h"
#include "BequestEquipmentBase.generated.h"

class UDataAsset_AbilitySystem;
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

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Bequest|EquipmentSystem")
	FBequestEquipmentData EquipmentData;
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Bequest|EquipmentSystem")
	USkeletalMeshComponent* EquipmentSkeletalMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Bequest|EquipmentSystem")
	UBoxComponent* EquipmentCollisionBox;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Bequest|EquipmentSystem")
	UNiagaraComponent* EquipmentTrailFX;

	UFUNCTION()
	virtual void OnCollisionBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	virtual void OnCollisionBoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

public:
	FORCEINLINE UBoxComponent* GetEquipmentCollisionBox() const { return EquipmentCollisionBox; }
	FORCEINLINE UNiagaraComponent* GetEquipmentTrailFX() const { return EquipmentTrailFX; }
	FORCEINLINE FBequestEquipmentData GetEquipmentData() const { return EquipmentData; }
};
