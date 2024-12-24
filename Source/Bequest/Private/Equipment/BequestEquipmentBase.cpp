// Copyright Yooshley. All rights reserved.


#include "Equipment/BequestEquipmentBase.h"

#include "BequestFunctionLibrary.h"
#include "Components/BoxComponent.h"


ABequestEquipmentBase::ABequestEquipmentBase()
{
	bReplicates = true;
	bNetLoadOnClient = true;
	PrimaryActorTick.bCanEverTick = false;

	EquipmentMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("EquipmentMesh"));
	SetRootComponent(EquipmentMesh);

	EquipmentCollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("EquipmentCollisionBox"));
	EquipmentCollisionBox->SetupAttachment(GetRootComponent());
	EquipmentCollisionBox->SetBoxExtent(FVector(20.f));
	EquipmentCollisionBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	EquipmentCollisionBox->OnComponentBeginOverlap.AddUniqueDynamic(this, &ThisClass::OnCollisionBoxBeginOverlap);
	EquipmentCollisionBox->OnComponentEndOverlap.AddUniqueDynamic(this, &ThisClass::OnCollisionBoxEndOverlap);
}

void ABequestEquipmentBase::OnCollisionBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	APawn* OwnerPawn = GetInstigator<APawn>();
	checkf(OwnerPawn, TEXT("Equipment Owning Pawn not assigned."));
	
	if (APawn* OtherPawn = Cast<APawn>(OtherActor))
	{
		if (OwnerPawn != OtherPawn)
		{
			OnEquipmentHitTargetBegin.ExecuteIfBound(OtherActor);
		}
		// if (UBequestFunctionLibrary::IsTargetPawnHostile(OwnerPawn, OtherPawn))
		// {
		// 	OnEquipmentHitTargetBegin.ExecuteIfBound(OtherActor);
		// }
	}
}

void ABequestEquipmentBase::OnCollisionBoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	APawn* OwnerPawn = GetInstigator<APawn>();
	checkf(OwnerPawn, TEXT("Weapon Owning Pawn not assigned."));

	if (APawn* OtherPawn = Cast<APawn>(OtherActor))
	{
		if (OwnerPawn != OtherPawn)
		{
			OnEquipmentHitTargetEnd.ExecuteIfBound(OtherActor);
		}
		// if (UBequestFunctionLibrary::IsTargetPawnHostile(OwnerPawn, OtherPawn))
		// {
		// 	OnEquipmentHitTargetEnd.ExecuteIfBound(OtherActor);
		// }
	}
}

