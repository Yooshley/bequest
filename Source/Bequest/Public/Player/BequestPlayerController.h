// Copyright Yooshley. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GenericTeamAgentInterface.h"
#include "GameFramework/PlayerController.h"
#include "BequestPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class BEQUEST_API ABequestPlayerController : public APlayerController, public IGenericTeamAgentInterface
{
	GENERATED_BODY()

public:
	ABequestPlayerController();
	
	//~ Begin IGenericTeamAgentInterface Interface.
	virtual FGenericTeamId GetGenericTeamId() const override;
	//~ End IGenericTeamAgentInterface Interface.
	
private:
	FGenericTeamId PlayerTeamId;
};
