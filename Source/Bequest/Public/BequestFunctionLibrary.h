// Copyright Yooshley. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "BequestFunctionLibrary.generated.h"

enum class EBequestConfirmType : uint8;
struct FGameplayTag;
class UBequestAbilitySystemComponent;

/**
 * 
 */

UCLASS()
class BEQUEST_API UBequestFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	static UBequestAbilitySystemComponent* NativeGetBequestASCFromActor(AActor* Actor);

	UFUNCTION(BlueprintCallable, Category = "Bequest|FunctionLibrary")
	static void AddGameplayTagToActor(AActor* Actor, FGameplayTag Tag);

	UFUNCTION(BlueprintCallable, Category = "Bequest|FunctionLibrary")
	static void RemoveGameplayTagFromActor(AActor* Actor, FGameplayTag Tag);

	static bool NativeCheckTagOnActor(AActor* Actor, FGameplayTag Tag);
	
	UFUNCTION(BlueprintCallable, Category = "Bequest|FunctionLibrary", meta=(ExpandEnumAsExecs = "ConfirmType"))
	static void CheckTagOnActor(AActor* Actor, FGameplayTag Tag, EBequestConfirmType& ConfirmType);
};
