#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "GameplayEffect.h"
#include "AttributeSetDataTableRow.generated.h"

USTRUCT(BlueprintType)
struct FAttributeSetDataTableRow : public FTableRowBase
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attribute Data")
	FGameplayAttribute Attribute;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attribute Data", meta = (ClampMin = "0.0", UIMin = "0.0"))
	float AttributeValue = 0.0f;
};
