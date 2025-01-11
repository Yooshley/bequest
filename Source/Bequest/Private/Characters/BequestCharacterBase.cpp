// Copyright Yooshley. All rights reserved.


#include "Characters/BequestCharacterBase.h"

#include "Components/BequestAbilitySystemComponent.h"
#include "Components/BequestEquipmentSystemComponent.h"
#include "MotionWarpingComponent.h"
#include "Actors/BequestWidgetActor.h"
#include "Components/WidgetComponent.h"
#include "Widgets/BequestAbilitySystemWidget.h"


ABequestCharacterBase::ABequestCharacterBase()
{
	bReplicates = true;
    bAlwaysRelevant = true;
	SetNetUpdateFrequency(66.f);
	SetMinNetUpdateFrequency(33.f);
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;

	BequestASC = CreateDefaultSubobject<UBequestAbilitySystemComponent>(TEXT("BequestASC"));
	BequestESC = CreateDefaultSubobject<UBequestEquipmentSystemComponent>(TEXT("BequestESC"));
	
	MotionWarpingComponent = CreateDefaultSubobject<UMotionWarpingComponent>(TEXT("MotionWarpingComponent"));
	StatsActorComponent = CreateDefaultSubobject<UChildActorComponent>(TEXT("StatsActor"));
	StatsActorComponent->SetupAttachment(GetMesh());
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

void ABequestCharacterBase::SetupCharacterStatsWidget()
{
	ABequestWidgetActor* WidgetActor = Cast<ABequestWidgetActor>(StatsActorComponent->GetChildActor());
	if (WidgetActor && StatsActorWidget)
	{
		WidgetActor->WidgetComponent->SetWidget(StatsActorWidget);
		StatsActorWidget->InitializeAbilitySystemWidget(BequestASC);
		FVector StatsWidgetLocation = FVector(0, 0, 175.f);
		if (IsLocallyControlled() && IsPlayerControlled())
		{
			StatsWidgetLocation = FVector(0, 0, -75.f);
		}
		StatsActorComponent->SetRelativeLocation(StatsWidgetLocation);
	}
}
