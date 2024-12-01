// Copyright Yooshley. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "BequestCharacterBase.generated.h"

class ABequestPlayerEquipment;
class UBequestAbilitySystemComponent;

UCLASS(Abstract, NotBlueprintable)
class BEQUEST_API ABequestCharacterBase : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	ABequestCharacterBase();
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = "Bequest|Equipment")
	ABequestPlayerEquipment* CurrentEquipment;

	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = "Bequest|Equipment")
	ABequestPlayerEquipment* EquippedEquipment;

protected:
	virtual void PossessedBy(AController* NewController) override;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Bequest|AbilitySystem")
	UBequestAbilitySystemComponent* BequestASC;

public:
	FORCEINLINE UBequestAbilitySystemComponent* GetBequestAbilitySystemComponent() const { return BequestASC; }
};
