// Copyright Yooshley. All rights reserved.


#include "Characters/BequestCharacterBase.h"

#include "Components/BequestAbilitySystemComponent.h"
#include "Net/UnrealNetwork.h"


ABequestCharacterBase::ABequestCharacterBase()
{
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;

	BequestASC = CreateDefaultSubobject<UBequestAbilitySystemComponent>(TEXT("BequestASC"));
}

void ABequestCharacterBase::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ThisClass, CurrentEquipment);
	DOREPLIFETIME(ThisClass, EquippedEquipment);
}

UAbilitySystemComponent* ABequestCharacterBase::GetAbilitySystemComponent() const
{
	return GetBequestAbilitySystemComponent();
}

void ABequestCharacterBase::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	if(BequestASC)
	{
		BequestASC->InitializeAbilitySystem(this, this);
	}
}
