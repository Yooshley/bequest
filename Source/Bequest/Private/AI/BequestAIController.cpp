// Copyright Yooshley. All rights reserved.


#include "AI/BequestAIController.h"

#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PawnMovementComponent.h"
#include "Navigation/CrowdFollowingComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"

ABequestAIController::ABequestAIController(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer.SetDefaultSubobjectClass<UCrowdFollowingComponent>("PathFollowingComponent"))
{
	SenseConfig_Sight = CreateDefaultSubobject<UAISenseConfig_Sight>("SenseConfig_Sight");
	SenseConfig_Sight->DetectionByAffiliation.bDetectEnemies = true;
	SenseConfig_Sight->DetectionByAffiliation.bDetectFriendlies = false;
	SenseConfig_Sight->DetectionByAffiliation.bDetectNeutrals = false;
	SenseConfig_Sight->SightRadius = 1000.f;
	SenseConfig_Sight->LoseSightRadius = 1000.f;
	SenseConfig_Sight->PeripheralVisionAngleDegrees = 360.f;

	PerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>("PerceptionComponent");
	PerceptionComponent->ConfigureSense(*SenseConfig_Sight);
	PerceptionComponent->SetDominantSense(UAISenseConfig_Sight::StaticClass());
	PerceptionComponent->OnTargetPerceptionUpdated.AddUniqueDynamic(this, &ThisClass::OnHostilePerceptionUpdated);

	AAIController::SetGenericTeamId(FGenericTeamId(1));
	
	
	Blackboard = CreateDefaultSubobject<UBlackboardComponent>("BlackboardComponent");
	check(Blackboard);
	BehaviorTreeComponent = CreateDefaultSubobject<UBehaviorTreeComponent>("BehaviorTreeComponent");
	check(BehaviorTreeComponent);
}

ETeamAttitude::Type ABequestAIController::GetTeamAttitudeTowards(const AActor& OtherActor) const
{
	const APawn* OtherPawn = Cast<const APawn>(&OtherActor);
	const IGenericTeamAgentInterface* OtherTeamAgent = Cast<const IGenericTeamAgentInterface>(OtherPawn->GetController());
	if (OtherTeamAgent && OtherTeamAgent->GetGenericTeamId() < GetGenericTeamId())
	{
		return ETeamAttitude::Hostile;
	}
	return ETeamAttitude::Friendly;
}

void ABequestAIController::BeginPlay()
{
	Super::BeginPlay();
	if (Blackboard)
	{
		Blackboard->SetValueAsFloat(FName("DefaultMoveSpeed"), GetCharacter()->GetCharacterMovement()->MaxWalkSpeed);
	}

	if (UCrowdFollowingComponent* CrowdFollowingComponent = Cast<UCrowdFollowingComponent>(GetPathFollowingComponent()))
	{
		CrowdFollowingComponent->SetCrowdSimulationState(bEnableDetourCrowdAvoidance? ECrowdSimulationState::Enabled : ECrowdSimulationState::Disabled);

		switch (DetourCrowdAvoidanceQuality)
		{
		case 1:
			CrowdFollowingComponent->SetCrowdAvoidanceQuality(ECrowdAvoidanceQuality::Low);
			break;
		case 2:
			CrowdFollowingComponent->SetCrowdAvoidanceQuality(ECrowdAvoidanceQuality::Medium);
			break;
		case 3:
			CrowdFollowingComponent->SetCrowdAvoidanceQuality(ECrowdAvoidanceQuality::Good);
			break;
		case 4:
			CrowdFollowingComponent->SetCrowdAvoidanceQuality(ECrowdAvoidanceQuality::High);
			break;
		default:
			CrowdFollowingComponent->SetCrowdAvoidanceQuality(ECrowdAvoidanceQuality::High);
			break;
		}

		CrowdFollowingComponent->SetAvoidanceGroup(1);
		CrowdFollowingComponent->SetGroupsToAvoid(1);
		CrowdFollowingComponent->SetCrowdCollisionQueryRange(CollisionQueryRange);
	}
}

void ABequestAIController::OnHostilePerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
	if (!Blackboard->GetValueAsObject(FName("TargetActor")))
	{
		if (Stimulus.WasSuccessfullySensed() && Actor)
		{
			Blackboard->SetValueAsObject(FName("TargetActor"), Actor);
		}
	}
}
