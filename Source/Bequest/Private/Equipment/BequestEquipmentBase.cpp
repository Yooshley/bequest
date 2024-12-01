// Copyright Yooshley. All rights reserved.


#include "Equipment/BequestEquipmentBase.h"

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
}

void ABequestEquipmentBase::OnCollisionBoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}

