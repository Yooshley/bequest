// Copyright Yooshley. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/PawnExtenstionComponentBase.h"
#include "BequestHUDComponent.generated.h"

class UBequestAbilitySystemWidget;
class UWidgetComponent;
/**
 * 
 */
UCLASS()
class BEQUEST_API UBequestHUDComponent : public UPawnExtenstionComponentBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UWidgetComponent* WidgetComponent;
};
