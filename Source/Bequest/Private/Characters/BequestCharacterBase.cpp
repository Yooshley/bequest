// Copyright Yooshley. All rights reserved.


#include "Characters/BequestCharacterBase.h"

#include "Components/BequestAbilitySystemComponent.h"
#include "Components/BequestEquipmentSystemComponent.h"
#include "Net/UnrealNetwork.h"


ABequestCharacterBase::ABequestCharacterBase()
{
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;

	BequestASC = CreateDefaultSubobject<UBequestAbilitySystemComponent>(TEXT("BequestASC"));
	BequestESC = CreateDefaultSubobject<UBequestEquipmentSystemComponent>(TEXT("BequestESC"));
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
