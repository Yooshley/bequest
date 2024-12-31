// Copyright Yooshley. All rights reserved.


#include "Characters/BequestCharacterBase.h"

#include "BequestDebugHelper.h"
#include "Components/BequestAbilitySystemComponent.h"
#include "Components/BequestEquipmentSystemComponent.h"
#include "MotionWarpingComponent.h"
#include "Components/WidgetComponent.h"


ABequestCharacterBase::ABequestCharacterBase()
{
	bReplicates = true;
    bAlwaysRelevant = true;
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;

	BequestASC = CreateDefaultSubobject<UBequestAbilitySystemComponent>(TEXT("BequestASC"));
	BequestESC = CreateDefaultSubobject<UBequestEquipmentSystemComponent>(TEXT("BequestESC"));
	
	MotionWarpingComponent = CreateDefaultSubobject<UMotionWarpingComponent>(TEXT("MotionWarpingComponent"));
	
	StatsActor = CreateDefaultSubobject<UChildActorComponent>(TEXT("StatsActor"));
	StatsActor->SetupAttachment(GetMesh());
}

UAbilitySystemComponent* ABequestCharacterBase::GetAbilitySystemComponent() const
{
	return BequestASC;
}

UBequestEquipmentSystemComponent* ABequestCharacterBase::GetEquipmentSystemComponent() const
{
	return BequestESC;
}

void ABequestCharacterBase::LinkAnimClassLayer(TSubclassOf<UAnimInstance> AnimLayerClass)
{
	if (HasAuthority())
	{
		Multicast_LinkAnimClassLayer(AnimLayerClass);
	}
}

void ABequestCharacterBase::UnlinkAnimClassLayer(TSubclassOf<UAnimInstance> AnimLayerClass)
{
	if (HasAuthority())
	{
		Multicast_UnlinkAnimClassLayer(AnimLayerClass);
	}
}

void ABequestCharacterBase::Multicast_LinkAnimClassLayer_Implementation(TSubclassOf<UAnimInstance> AnimLayerClass)
{
	GetMesh()->LinkAnimClassLayers(AnimLayerClass);
}

void ABequestCharacterBase::Multicast_UnlinkAnimClassLayer_Implementation(TSubclassOf<UAnimInstance> AnimLayerClass)
{
	GetMesh()->UnlinkAnimClassLayers(AnimLayerClass);
}

void ABequestCharacterBase::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	if(BequestASC)
	{
		BequestASC->InitializeAbilitySystem(this, this);
		PostInitializeAbilitySystem();
	}
}
