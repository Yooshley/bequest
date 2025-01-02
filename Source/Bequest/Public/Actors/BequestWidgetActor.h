// Copyright Yooshley. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BequestWidgetActor.generated.h"

class UBequestAbilitySystemWidget;
class UWidgetComponent;

UCLASS()
class BEQUEST_API ABequestWidgetActor : public AActor
{
	GENERATED_BODY()
	
public:	
	ABequestWidgetActor();

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UWidgetComponent* WidgetComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UBequestAbilitySystemWidget* StatsWidget;
};
