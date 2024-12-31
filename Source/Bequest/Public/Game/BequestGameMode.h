// Copyright Yooshley. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "BequestGameMode.generated.h"

/**
 * 
 */
UCLASS()
class BEQUEST_API ABequestGameMode : public AGameMode
{
	GENERATED_BODY()

public:
	ABequestGameMode();

protected:
	virtual void OnPostLogin(AController* NewPlayer) override;

public:
	UPROPERTY(VisibleAnywhere, blueprintReadOnly)
	TArray<AController*> PlayerArray;
};
