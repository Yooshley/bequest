// Copyright Yooshley. All rights reserved.


#include "Characters/BequestCharacterBase.h"

#include "Components/BequestAbilitySystemComponent.h"
#include "Components/BequestEquipmentSystemComponent.h"
#include "MotionWarpingComponent.h"


ABequestCharacterBase::ABequestCharacterBase()
{
	bReplicates = true;
    bAlwaysRelevant = true;
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;

	BequestASC = CreateDefaultSubobject<UBequestAbilitySystemComponent>(TEXT("BequestASC"));
	BequestESC = CreateDefaultSubobject<UBequestEquipmentSystemComponent>(TEXT("BequestESC"));
	
	MotionWarpingComponent = CreateDefaultSubobject<UMotionWarpingComponent>(TEXT("MotionWarpingComponent"));
}

UAbilitySystemComponent* ABequestCharacterBase::GetAbilitySystemComponent() const
{
	return GetBequestAbilitySystemComponent();
}

void ABequestCharacterBase::LinkAnimClassLayer(TSubclassOf<UAnimInstance> AnimLayerClass)
{
	if (HasAuthority())
	{
		MulticastLinkAnimClassLayer(AnimLayerClass);
	}
}

void ABequestCharacterBase::UnlinkAnimClassLayer(TSubclassOf<UAnimInstance> AnimLayerClass)
{
	if (HasAuthority())
	{
		MulticastUnlinkAnimClassLayer(AnimLayerClass);
	}
}

void ABequestCharacterBase::MulticastLinkAnimClassLayer_Implementation(TSubclassOf<UAnimInstance> AnimLayerClass)
{
	GetMesh()->LinkAnimClassLayers(AnimLayerClass);
}

void ABequestCharacterBase::MulticastUnlinkAnimClassLayer_Implementation(TSubclassOf<UAnimInstance> AnimLayerClass)
{
	GetMesh()->UnlinkAnimClassLayers(AnimLayerClass);
}

void ABequestCharacterBase::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	if(BequestASC)
	{
		BequestASC->InitializeAbilitySystem(this, this);
	}
}
