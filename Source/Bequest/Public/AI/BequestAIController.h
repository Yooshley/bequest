// Copyright Yooshley. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BequestAIController.generated.h"

struct FAIStimulus;
class UAISenseConfig_Sight;
class UBehaviorTreeComponent;
class UAIPerceptionComponent;
/**
 * 
 */
UCLASS()
class BEQUEST_API ABequestAIController : public AAIController
{
	GENERATED_BODY()

public:
	ABequestAIController(const FObjectInitializer& ObjectInitializer);

	//Begin IGenericTeamAgentInterface
	virtual ETeamAttitude::Type GetTeamAttitudeTowards(const AActor& OtherActor) const override;
	//End IGenericTeamAgentInterface

protected:
	virtual void BeginPlay() override;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UAISenseConfig_Sight* SenseConfig_Sight;

	UFUNCTION()
	virtual void OnHostilePerceptionUpdated(AActor* Actor, FAIStimulus Stimulus);
	
	UPROPERTY()
	TObjectPtr<UBehaviorTreeComponent> BehaviorTreeComponent;

private:
	UPROPERTY(EditDefaultsOnly, Category = "Bequest|DetourCrowdAvoidance")
	bool bEnableDetourCrowdAvoidance = true;

	UPROPERTY(EditDefaultsOnly, Category = "Bequest|DetourCrowdAvoidance", meta = (EditCondition = "bEnableDetourCrowdAvoidance", UIMin = "1", UIMax = "4"))
	int32 DetourCrowdAvoidanceQuality = 4;

	UPROPERTY(EditDefaultsOnly, Category = "Bequest|DetourCrowdAvoidance")
	float CollisionQueryRange = 500.f;
};
