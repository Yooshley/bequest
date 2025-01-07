// Copyright Yooshley. All rights reserved.


#include "Characters/BequestWorldCharacter.h"

#include "AI/BequestAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/BequestAbilitySystemComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

ABequestWorldCharacter::ABequestWorldCharacter()
{
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bUseControllerDesiredRotation = true;
}

void ABequestWorldCharacter::BeginPlay()
{
	Super::BeginPlay();
	if(BequestASC)
	{
		BequestASC->InitializeAbilitySystem(this, this);
		SetupCharacterStatsWidget();
	}
}

void ABequestWorldCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	if (!HasAuthority()) return;
	BequestAIC = Cast<ABequestAIController>(NewController);
	BequestAIC->GetBlackboardComponent()->InitializeBlackboard(*BehaviorTree->BlackboardAsset);
	BequestAIC->RunBehaviorTree(BehaviorTree);
}

