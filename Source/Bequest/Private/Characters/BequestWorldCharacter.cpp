// Copyright Yooshley. All rights reserved.


#include "Characters/BequestWorldCharacter.h"

#include "Components/BequestAbilitySystemComponent.h"

void ABequestWorldCharacter::BeginPlay()
{
	Super::BeginPlay();
	if(BequestASC)
	{
		BequestASC->InitializeAbilitySystem(this, this);
		SetupCharacterStatsWidget();
	}
}

void ABequestWorldCharacter::PostNetReceive()
{
	Super::PostNetReceive();
	if(BequestASC)
	{
		BequestASC->InitializeAbilitySystem(this, this);
		SetupCharacterStatsWidget();
	}
}
