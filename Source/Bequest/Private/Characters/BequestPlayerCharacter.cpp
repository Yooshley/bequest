// Copyright Yooshley. All rights reserved.


#include "Characters/BequestPlayerCharacter.h"

#include <string>

#include "BequestDebugHelper.h"
#include "EnhancedInputSubsystems.h"
#include "Camera/CameraComponent.h"
#include "Components/BequestAbilitySystemComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Net/UnrealNetwork.h"

ABequestPlayerCharacter::ABequestPlayerCharacter()
{
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(GetRootComponent());
	CameraBoom->TargetArmLength = 500.f;
	CameraBoom->SocketOffset = FVector(0.f,50.f,500.f);
	CameraBoom->bUsePawnControlRotation = true;
	
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom,USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f,500.f,0.f);
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 500.f;

	//TODO: Create proper Equipment System
	//Equipment Components
	HeadEquipment =  CreateDefaultSubobject<UStaticMeshComponent>(TEXT("HeadEquipment"));
	HeadEquipment->SetupAttachment(GetMesh(), TEXT("headSocket"));
	ShoulderEquipment =  CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("ShoulderEquipment"));
	ShoulderEquipment->SetupAttachment(GetMesh());
	ShoulderEquipment->SetLeaderPoseComponent(GetMesh());
	BackEquipment =  CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("BackEquipment"));
	BackEquipment->SetupAttachment(GetMesh());
	BackEquipment->SetLeaderPoseComponent(GetMesh());
	TorsoEquipment =  CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("TorsoEquipment"));
	TorsoEquipment->SetupAttachment(GetMesh());
	TorsoEquipment->SetLeaderPoseComponent(GetMesh());
}

void ABequestPlayerCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	const ULocalPlayer* LocalPlayer = GetController<APlayerController>()->GetLocalPlayer();
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(LocalPlayer);

	check(Subsystem);
	Subsystem->AddMappingContext(InputMappingContext, 0);
}

void ABequestPlayerCharacter::Move(const FVector2D MovementVector)
{
	if (MovementVector.Y != 0.f)
    {
        AddMovementInput(FVector::ForwardVector, MovementVector.Y);
    }
    if (MovementVector.X != 0.f)
    {
        AddMovementInput(FVector::RightVector, MovementVector.X);
    }
}

void ABequestPlayerCharacter::Turn(const FVector2D TurnVector)
{
	if (bUseControllerRotationYaw)
    {
        const float AngleRadians = FMath::Atan2(TurnVector.X, TurnVector.Y);
        const float AngleDegrees = FMath::RadiansToDegrees(AngleRadians);
        const FRotator TargetRotation = FRotator(0, AngleDegrees, 0);
		
        const FRotator CurrentRotation = Controller->GetControlRotation();
        const FRotator TurnRotation = FMath::RInterpTo(CurrentRotation, TargetRotation, GetWorld()->DeltaTimeSeconds, TurnSpeed);

        Controller->SetControlRotation(TurnRotation);
    }
}

void ABequestPlayerCharacter::ToggleTurn(bool bEnable)
{
	Controller->SetControlRotation(GetActorRotation());
	bUseControllerRotationYaw = bEnable;
}

void ABequestPlayerCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
	if(BequestASC)
	{
		BequestASC->InitializeAbilitySystem(this, this);
		SetupCharacterStatsWidget();
	}
}

void ABequestPlayerCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	if(BequestASC)
	{
		BequestASC->InitializeAbilitySystem(this, this);
		SetupCharacterStatsWidget();
	}
}

void ABequestPlayerCharacter::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ABequestPlayerCharacter, EquipmentColorIndex);
}

void ABequestPlayerCharacter::OnRep_EquipmentColorIndex()
{
	SetEquipmentColor(EquipmentColorIndex);
}

void ABequestPlayerCharacter::SetEquipmentColor(int8 ColorIndex)
{
	if (BackEquipment)
	{
		UMaterialInstanceDynamic* BackDynamicMaterial = BackEquipment->CreateAndSetMaterialInstanceDynamic(0);
		if (BackDynamicMaterial)
		{
			BackDynamicMaterial->SetScalarParameterValue(FName("ColorIndex"), ColorIndex);
		}
	}
	if (HeadEquipment)
	{
		UMaterialInstanceDynamic* HeadDynamicMaterial = HeadEquipment->CreateAndSetMaterialInstanceDynamic(0);
		if (HeadDynamicMaterial)
		{
			HeadDynamicMaterial->SetScalarParameterValue(FName("ColorIndex"), ColorIndex);
		}
	}
}
