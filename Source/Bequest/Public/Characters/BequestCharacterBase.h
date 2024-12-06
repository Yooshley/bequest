// Copyright Yooshley. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "BequestCharacterBase.generated.h"

class UBequestEquipmentSystemComponent;
class ABequestPlayerEquipment;
class UBequestAbilitySystemComponent;
class UMotionWarpingComponent;

UCLASS(Abstract, NotBlueprintable)
class BEQUEST_API ABequestCharacterBase : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	ABequestCharacterBase();
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	
	UFUNCTION(BlueprintCallable, Category = "Bequest|Animation")
	void LinkAnimClassLayer(TSubclassOf<UAnimInstance> AnimLayerClass);

	UFUNCTION(BlueprintCallable, Category = "Bequest|Animation")
	void UnlinkAnimClassLayer(TSubclassOf<UAnimInstance> AnimLayerClass);

protected:
	virtual void PossessedBy(AController* NewController) override;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Bequest|AbilitySystem")
	UBequestAbilitySystemComponent* BequestASC;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Bequest|EquipmentSystem")
	UBequestEquipmentSystemComponent* BequestESC;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Bequest|Animation")
    UMotionWarpingComponent* MotionWarpingComponent;

private:
	UFUNCTION(NetMulticast, Reliable)
	void MulticastLinkAnimClassLayer(TSubclassOf<UAnimInstance> AnimLayerClass);
	
	UFUNCTION(NetMulticast, Reliable)
	void MulticastUnlinkAnimClassLayer(TSubclassOf<UAnimInstance> AnimLayerClass);

public:
	FORCEINLINE UBequestAbilitySystemComponent* GetBequestAbilitySystemComponent() const { return BequestASC; }
	FORCEINLINE UBequestEquipmentSystemComponent* GetBequestEquipmentSystemComponent() const { return BequestESC; }
};
