// Copyright Yooshley. All rights reserved.


#include "Actors/BequestWidgetActor.h"

#include "Components/WidgetComponent.h"

ABequestWidgetActor::ABequestWidgetActor()
{
	PrimaryActorTick.bCanEverTick = false;

	WidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("WidgetComponent"));
}


