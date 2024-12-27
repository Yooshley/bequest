// Copyright Yooshley. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "BequestFunctionLibrary.generated.h"

struct FGameplayEventData;
enum class EBequestValidType : uint8;
class UBequestEquipmentSystemComponent;
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
	static void AddTagWithReferenceCounting(AActor* Actor, FGameplayTag Tag);

	UFUNCTION(BlueprintCallable, Category = "Bequest|FunctionLibrary")
	static void RemoveTagWithReferenceCounting(AActor* Actor, FGameplayTag Tag);

	UFUNCTION(BlueprintCallable, Category = "Bequest|FunctionLibrary")
	static void AddGameplayTag(AActor* Actor, FGameplayTag Tag);

	UFUNCTION(BlueprintCallable, Category = "Bequest|FunctionLibrary")
	static void RemoveGameplayTag(AActor* Actor, FGameplayTag Tag);

	static bool NativeCheckTagOnActor(AActor* Actor, FGameplayTag Tag);
	
	UFUNCTION(BlueprintCallable, Category = "Bequest|FunctionLibrary", meta=(ExpandEnumAsExecs = "ConfirmType"))
	static void CheckTagOnActor(AActor* Actor, FGameplayTag Tag, EBequestConfirmType& ConfirmType);

	static UBequestEquipmentSystemComponent* NativeGetEquipmentSystemComponentFromActor(AActor* Actor);

	UFUNCTION(BlueprintCallable, Category = "Bequest|FunctionLibrary", meta=(ExpandEnumAsExecs = "ValidType"))
	static UBequestEquipmentSystemComponent* GetEquipmentSystemComponentFromActor(AActor* Actor, EBequestValidType& ValidType); 

	UFUNCTION(BlueprintPure, Category = "Bequest|FunctionLibrary")
	static bool IsTargetPawnHostile(APawn* QueryPawn, APawn* TargetPawn);

	UFUNCTION(BlueprintPure, Category = "Bequest|FunctionLibrary")
	static FGameplayTag ComputeHitReactDirectionTag(AActor* Instigator, AActor* HitActor, float& AngleDifference);
};
