// Copyright Yooshley. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Characters/BequestCharacterBase.h"
#include "BequestWorldCharacter.generated.h"

class UBehaviorTree;
class ABequestAIController;

/**
 * 
 */
UCLASS(Blueprintable)
class BEQUEST_API ABequestWorldCharacter : public ABequestCharacterBase
{
	GENERATED_BODY()
	
public:
	ABequestWorldCharacter();
	
protected:
	virtual void BeginPlay() override;
	virtual void PossessedBy(AController* NewController) override;

	UPROPERTY(EditAnywhere, Category= "Bequest|AI")
	TObjectPtr<UBehaviorTree> BehaviorTree;
	
	UPROPERTY()
	TObjectPtr<ABequestAIController> BequestAIC;
};
