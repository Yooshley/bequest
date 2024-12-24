// Copyright Yooshley. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "EquipmentSystemInterface.generated.h"

class UBequestEquipmentSystemComponent;
// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UEquipmentSystemInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class BEQUEST_API IEquipmentSystemInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual UBequestEquipmentSystemComponent* GetEquipmentSystemComponent() const = 0;
};
