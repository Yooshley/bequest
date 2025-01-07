// Copyright Yooshley. All rights reserved.


#include "Components/BequestEquipmentSystemComponent.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "BequestGameplayTags.h"
#include "GameplayTagContainer.h"
#include "Abilities/GameplayAbilityTypes.h"
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

void UBequestEquipmentSystemComponent::RegisterEquipment(ABequestEquipmentBase* Equipment)
{
	check(Equipment);
	check(Equipment->GetEquipmentData().EquipmentTag.IsValid()); 

	CarriedEquipment.Emplace(Equipment);

	Equipment->OnEquipmentHitTargetBegin.BindUObject(this, &ThisClass::OnEquipmentHitTargetActorBegin);
	Equipment->OnEquipmentHitTargetEnd.BindUObject(this, &ThisClass::OnEquipmentHitTargetActorEnd);
}

ABequestEquipmentBase* UBequestEquipmentSystemComponent::GetCarriedEquipmentByTag(FGameplayTag EquipmentTag) const
{
	for (ABequestEquipmentBase* Equipment : CarriedEquipment)
	{
		if (Equipment && Equipment->GetEquipmentData().EquipmentTag == EquipmentTag)
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

	if (Equipment->GetEquipmentCollisionBox())
	{
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
}

void UBequestEquipmentSystemComponent::ToggleEquipmentTrail(bool bShouldEnable)
{
	ABequestEquipmentBase* Equipment = GetEquippedEquipment();
	check(Equipment);
	
	if (Equipment->GetEquipmentTrailFX())
	{
		if (bShouldEnable)
		{
			Equipment->GetEquipmentTrailFX()->Activate();
		}
		else
		{
			Equipment->GetEquipmentTrailFX()->Deactivate();
		}
	}
}

void UBequestEquipmentSystemComponent::OnEquipmentHitTargetActorBegin(AActor* HitActor)
{
	if (EquipmentOverlappedActors.Contains(HitActor)) return;
	EquipmentOverlappedActors.AddUnique(HitActor);

	FGameplayEventData Data;
	Data.Instigator = GetOwningPawn();
	Data.Target = HitActor;
	
	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(GetOwningPawn(),BequestGameplayTags::Character_Event_Hit,Data);
}

void UBequestEquipmentSystemComponent::OnEquipmentHitTargetActorEnd(AActor* HitActor)
{
}

void UBequestEquipmentSystemComponent::IncrementMontage()
{
	ABequestEquipmentBase* Equipment = GetEquippedEquipment();
	if (Equipment == nullptr) return;
	MontageIndex++;
	if (MontageIndex > Equipment->EquipmentData.EquipmentMontageMap.Num())
	{
		MontageIndex = 1;
	}
}

UAnimMontage* UBequestEquipmentSystemComponent::GetEquipmentMontage(bool bAlternateMontage)
{
	ABequestEquipmentBase* Equipment = GetEquippedEquipment();
	if (Equipment == nullptr) return nullptr;
	if (bAlternateMontage)
	{
		return Equipment->EquipmentData.EquipmentAlternateMontageMap[MontageIndex];
	}
	return Equipment->EquipmentData.EquipmentMontageMap[MontageIndex];
}

TSubclassOf<UBequestCharacterLinkedAnimLayer> UBequestEquipmentSystemComponent::GetEquipmentAnimLayer()
{
	ABequestEquipmentBase* Equipment = GetEquippedEquipment();
	if (Equipment == nullptr) return nullptr;
	return Equipment->EquipmentData.EquipmentAnimLayerToLink;
}
