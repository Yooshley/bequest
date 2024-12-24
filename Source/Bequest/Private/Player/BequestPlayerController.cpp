// Copyright Yooshley. All rights reserved.


#include "Player/BequestPlayerController.h"

#include "BequestDebugHelper.h"

ABequestPlayerController::ABequestPlayerController()
{
	PlayerTeamId = FGenericTeamId(0);
}

FGenericTeamId ABequestPlayerController::GetGenericTeamId() const
{
	return PlayerTeamId;
}
