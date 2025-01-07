// Copyright Yooshley. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "Interfaces/EquipmentSystemInterface.h"
#include "BequestCharacterBase.generated.h"

class UBequestHUDComponent;
class ABequestWidgetActor;
class UBequestAbilitySystemWidget;
class UBequestEquipmentSystemComponent;
class ABequestPlayerEquipment;
class UBequestAbilitySystemComponent;
class UMotionWarpingComponent;

UCLASS(Abstract, NotBlueprintable)
class BEQUEST_API ABequestCharacterBase : public ACharacter, public IAbilitySystemInterface, public IEquipmentSystemInterface
{
	GENERATED_BODY()

public:
	ABequestCharacterBase();
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	virtual UBequestEquipmentSystemComponent* GetEquipmentSystemComponent() const override;

	UFUNCTION(BlueprintImplementableEvent)
	void PostInitializeAbilitySystem();
	
	UFUNCTION(BlueprintCallable, Category = "Bequest|Animation")
	void LinkAnimClassLayer(TSubclassOf<UAnimInstance> AnimLayerClass);

	UFUNCTION(BlueprintCallable, Category = "Bequest|Animation")
	void UnlinkAnimClassLayer(TSubclassOf<UAnimInstance> AnimLayerClass);

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Bequest|AbilitySystem")
	UBequestAbilitySystemComponent* BequestASC;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Bequest|EquipmentSystem")
	UBequestEquipmentSystemComponent* BequestESC;
	
	UPROPERTY(BlueprintReadOnly, Category = "Bequest|Animation")
    UMotionWarpingComponent* MotionWarpingComponent;
    
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    UChildActorComponent* StatsActorComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UBequestAbilitySystemWidget* StatsActorWidget;

	UFUNCTION()
	void SetupCharacterStatsWidget();

private:
	UFUNCTION(NetMulticast, Reliable)
	void Multicast_LinkAnimClassLayer(TSubclassOf<UAnimInstance> AnimLayerClass);
	
	UFUNCTION(NetMulticast, Reliable)
	void Multicast_UnlinkAnimClassLayer(TSubclassOf<UAnimInstance> AnimLayerClass);

public:
	FORCEINLINE UMotionWarpingComponent* GetMotionWarpingComponent() const { return MotionWarpingComponent; }
	FORCEINLINE UBequestAbilitySystemComponent* GetBequestAbilitySystemComponent() const { return BequestASC; }
	FORCEINLINE UBequestEquipmentSystemComponent* GetBequestEquipmentSystemComponent() const { return BequestESC; }
};
