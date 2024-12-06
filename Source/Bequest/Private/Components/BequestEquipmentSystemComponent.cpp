// Copyright Yooshley. All rights reserved.


#include "Components/BequestEquipmentSystemComponent.h"

#include "GameplayTagContainer.h"
#include "Components/BoxComponent.h"
#include "Data/DataAsset_AbilityData.h"
#include "Equipment/BequestEquipmentBase.h"
#include "Net/UnrealNetwork.h"

UBequestEquipmentSystemComponent::UBequestEquipmentSystemComponent()
{
	SetIsReplicatedByDefault(true);
}

void UBequestEquipmentSystemComponent::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ThisClass, CarriedEquipment);
	DOREPLIFETIME(ThisClass, EquippedEquipmentTag);
}

void UBequestEquipmentSystemComponent::RegisterEquipment(ABequestEquipmentBase* Equipment, bool bRegisterEquipped)
{
	check(Equipment);
	check(Equipment->GetEquipmentTag().IsValid()); 

	CarriedEquipment.Emplace(Equipment);

	Equipment->OnEquipmentHitTargetBegin.BindUObject(this, &ThisClass::OnEquipmentHitTargetActorBegin);
	Equipment->OnEquipmentHitTargetEnd.BindUObject(this, &ThisClass::OnEquipmentHitTargetActorEnd);
	
	if(bRegisterEquipped)
	{
		EquippedEquipmentTag = Equipment->GetEquipmentTag();
	}
}

ABequestEquipmentBase* UBequestEquipmentSystemComponent::GetCarriedEquipmentByTag(FGameplayTag EquipmentTag) const
{
	for (ABequestEquipmentBase* Equipment : CarriedEquipment)
	{
		if (Equipment && Equipment->GetEquipmentTag() == EquipmentTag)
		{
			return Equipment;
		}
	}
	return nullptr;
}

ABequestEquipmentBase* UBequestEquipmentSystemComponent::GetEquippedEquipment() const
{
	if(!EquippedEquipmentTag.IsValid())
	{
		return nullptr;
	}
	return GetCarriedEquipmentByTag(EquippedEquipmentTag);
}

void UBequestEquipmentSystemComponent::ToggleEquipmentCollision(bool bShouldEnable)
{
	ABequestEquipmentBase* Equipment = GetEquippedEquipment();
	check(Equipment);

	if (bShouldEnable)
	{
		Equipment->GetEquipmentCollisionBox()->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	}
	else
	{
		Equipment->GetEquipmentCollisionBox()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		EquipmentOverlappedActors.Empty();
	}
}

void UBequestEquipmentSystemComponent::OnEquipmentHitTargetActorBegin(AActor* HitActor)
{
}

void UBequestEquipmentSystemComponent::OnEquipmentHitTargetActorEnd(AActor* HitActor)
{
}
