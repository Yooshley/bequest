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
	
	OverheadWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("OverheadWidget"));
	OverheadWidget->SetupAttachment(GetMesh());
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
		PostInitializeAbilitySystem();
		//InitializeAbilitySystemWidget();
	}
}

// void ABequestCharacterBase::InitializeAbilitySystemWidget() const
// {
// 	if (!AbilitySystemWidgetClass || !AbilitySystemWidget) return;
//
// 	UBequestAbilitySystemWidget* WidgetInstance = CreateWidget<UBequestAbilitySystemWidget>(AbilitySystemWidgetClass);
// 	if (WidgetInstance)
// 	{
// 		AbilitySystemWidget->SetWidget(WidgetInstance);
// 		if (IsLocallyControlled())
// 		{
// 			AbilitySystemWidget->SetRelativeLocation(FVector(0.f, 0.f, -50.f));
// 		}
// 		else
// 		{
// 			AbilitySystemWidget->SetRelativeLocation(FVector(0.f, 0.f, 200.f));
// 		}
// 		WidgetInstance->InitializeAbilitySystemWidget(GetAbilitySystemComponent());
// 	}
// }
