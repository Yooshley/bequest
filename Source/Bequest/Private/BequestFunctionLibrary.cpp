// Copyright Yooshley. All rights reserved.


#include "BequestFunctionLibrary.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "GameplayTagContainer.h"
#include "Components/BequestAbilitySystemComponent.h"
#include "Types/BequestEnumTypes.h"

UBequestAbilitySystemComponent* UBequestFunctionLibrary::NativeGetBequestASCFromActor(AActor* Actor)
{
	check(Actor);
	return CastChecked<UBequestAbilitySystemComponent>(UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Actor));
}

void UBequestFunctionLibrary::AddGameplayTagToActor(AActor* Actor, FGameplayTag Tag)
{
	UBequestAbilitySystemComponent* BequestASC = NativeGetBequestASCFromActor(Actor);
	if(!BequestASC->HasMatchingGameplayTag(Tag))
	{
		BequestASC->AddLooseGameplayTag(Tag); // Adding for server
		BequestASC->AddReplicatedLooseGameplayTag(Tag);
	}
}

void UBequestFunctionLibrary::RemoveGameplayTagFromActor(AActor* Actor, FGameplayTag Tag)
{
	UBequestAbilitySystemComponent* BequestASC = NativeGetBequestASCFromActor(Actor);
	if(BequestASC->HasMatchingGameplayTag(Tag))
	{
		BequestASC->RemoveLooseGameplayTag(Tag);  // Removing for server
		BequestASC->RemoveReplicatedLooseGameplayTag(Tag);
	}
}

bool UBequestFunctionLibrary::NativeCheckTagOnActor(AActor* Actor, FGameplayTag Tag)
{
	UBequestAbilitySystemComponent* BequestASC = NativeGetBequestASCFromActor(Actor);
	return BequestASC->HasMatchingGameplayTag(Tag);
}

void UBequestFunctionLibrary::CheckTagOnActor(AActor* Actor, FGameplayTag Tag, EBequestConfirmType& ConfirmType)
{
	ConfirmType = NativeCheckTagOnActor(Actor, Tag) ? EBequestConfirmType::Yes : EBequestConfirmType::No;
}
