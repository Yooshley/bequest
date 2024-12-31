// Copyright Yooshley. All rights reserved.


#include "Player/BequestPlayerController.h"
#include "GameFramework/PlayerState.h"

ABequestPlayerController::ABequestPlayerController()
{
	PlayerTeamId = FGenericTeamId(0);
}

FGenericTeamId ABequestPlayerController::GetGenericTeamId() const
{
	return PlayerTeamId;
}
