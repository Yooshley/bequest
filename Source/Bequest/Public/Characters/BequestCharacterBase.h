// Copyright Yooshley. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "BequestCharacterBase.generated.h"

class UBequestEquipmentSystemComponent;
class ABequestPlayerEquipment;
class UBequestAbilitySystemComponent;

UCLASS(Abstract, NotBlueprintable)
class BEQUEST_API ABequestCharacterBase : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	ABequestCharacterBase();
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

protected:
	virtual void PossessedBy(AController* NewController) override;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Bequest|AbilitySystem")
	UBequestAbilitySystemComponent* BequestASC;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Bequest|EquipmentSystem")
	UBequestEquipmentSystemComponent* BequestESC;

public:
	FORCEINLINE UBequestAbilitySystemComponent* GetBequestAbilitySystemComponent() const { return BequestASC; }
	FORCEINLINE UBequestEquipmentSystemComponent* GetBequestEquipmentSystemComponent() const { return BequestESC; }
};
