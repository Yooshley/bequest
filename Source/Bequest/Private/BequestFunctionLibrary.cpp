// Copyright Yooshley. All rights reserved.


#include "BequestFunctionLibrary.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "BequestGameplayTags.h"
#include "GameplayTagContainer.h"
#include "GenericTeamAgentInterface.h"
#include "Components/BequestAbilitySystemComponent.h"
#include "Interfaces/EquipmentSystemInterface.h"
#include "Kismet/KismetMathLibrary.h"
#include "Types/BequestEnumTypes.h"

UBequestAbilitySystemComponent* UBequestFunctionLibrary::NativeGetBequestASCFromActor(AActor* Actor)
{
	check(Actor);
	return CastChecked<UBequestAbilitySystemComponent>(UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Actor));
}

void UBequestFunctionLibrary::AddTagWithReferenceCounting(AActor* Actor, FGameplayTag Tag)
{
	if (!Tag.IsValid()) return;
	UBequestAbilitySystemComponent* BequestASC = NativeGetBequestASCFromActor(Actor);

	int32& Count = BequestASC->TagReferenceCount.FindOrAdd(Tag);
	Count++;
	if (Count == 1)
	{
		AddGameplayTag(Actor, Tag);
	}
}

void UBequestFunctionLibrary::RemoveTagWithReferenceCounting(AActor* Actor, FGameplayTag Tag)
{
	if (!Tag.IsValid()) return;
	UBequestAbilitySystemComponent* BequestASC = NativeGetBequestASCFromActor(Actor);

	int32* CountPtr = BequestASC->TagReferenceCount.Find(Tag);
	if (CountPtr && *CountPtr > 0)
	{
		(*CountPtr)--;
		if (*CountPtr == 0)
		{
			RemoveGameplayTag(Actor, Tag);
		}
	}
}

void UBequestFunctionLibrary::AddGameplayTag(AActor* Actor, FGameplayTag Tag)
{
	if (!Tag.IsValid()) return;
	UBequestAbilitySystemComponent* BequestASC = NativeGetBequestASCFromActor(Actor);
	if(!BequestASC->HasMatchingGameplayTag(Tag))
	{
		BequestASC->AddLooseGameplayTag(Tag); // Adding for server
		BequestASC->AddReplicatedLooseGameplayTag(Tag);
	}
}

void UBequestFunctionLibrary::RemoveGameplayTag(AActor* Actor, FGameplayTag Tag)
{
	if (!Tag.IsValid()) return;
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
    if (!Actor)
    {
        FFrame::KismetExecutionMessage(TEXT("Actor parameter is not assigned or invalid!"), ELogVerbosity::Error);
        ConfirmType = EBequestConfirmType::No;
        return;
    }
    if (!Tag.IsValid())
    {
        FFrame::KismetExecutionMessage(TEXT("Tag parameter is not assigned or invalid!"), ELogVerbosity::Error);
        ConfirmType = EBequestConfirmType::No;
        return;
    }
    ConfirmType = NativeCheckTagOnActor(Actor, Tag) ? EBequestConfirmType::Yes : EBequestConfirmType::No;
}

UBequestEquipmentSystemComponent* UBequestFunctionLibrary::NativeGetEquipmentSystemComponentFromActor(AActor* Actor)
{
	check(Actor);
	
	if (IEquipmentSystemInterface* EquipmentSystemInterface = Cast<IEquipmentSystemInterface>(Actor))
	{
		return EquipmentSystemInterface->GetEquipmentSystemComponent();
	}

	return nullptr;
}

UBequestEquipmentSystemComponent* UBequestFunctionLibrary::GetEquipmentSystemComponentFromActor(AActor* Actor, EBequestValidType& ValidType)
{
	UBequestEquipmentSystemComponent* EquipmentSystemComponent = NativeGetEquipmentSystemComponentFromActor(Actor);
	ValidType = EquipmentSystemComponent ? EBequestValidType::Valid : EBequestValidType::Invalid;
	return EquipmentSystemComponent;
}

bool UBequestFunctionLibrary::IsTargetPawnHostile(APawn* QueryPawn, APawn* TargetPawn)
{
	check(QueryPawn);
	check(TargetPawn);
	
	IGenericTeamAgentInterface* QueryAgent = Cast<IGenericTeamAgentInterface>(QueryPawn->GetController());
	IGenericTeamAgentInterface* TargetAgent = Cast<IGenericTeamAgentInterface>(TargetPawn->GetController());

	if (QueryAgent && TargetAgent)
	{
		return QueryAgent->GetGenericTeamId() != TargetAgent->GetGenericTeamId();
	}

	return false;
}

FGameplayTag UBequestFunctionLibrary::ComputeHitReactDirectionTag(AActor* Instigator, AActor* HitActor,
	float& AngleDifference)
{
	check(Instigator && HitActor);

	const FVector HitActorForward = HitActor->GetActorForwardVector();
	const FVector HitActorToInstigatorNormalized = (Instigator->GetActorLocation() - HitActor->GetActorLocation()).GetSafeNormal();

	const float DotResult = FVector::DotProduct(HitActorForward, HitActorToInstigatorNormalized);
	AngleDifference = UKismetMathLibrary::DegAcos(DotResult);

	const FVector CrossResult = FVector::CrossProduct(HitActorForward, HitActorToInstigatorNormalized);
	if (CrossResult.Z < 0.0f)
	{
		AngleDifference *= -1.f;
	}

	if (AngleDifference >= -45.f && AngleDifference <= 45.f)
	{
		return BequestGameplayTags::Character_Event_Hurt_Front;
	}
	else if (AngleDifference <= -135.f || AngleDifference >= 135.f)
	{
		return BequestGameplayTags::Character_Event_Hurt_Back;
	}
	else if (AngleDifference < -45.f && AngleDifference > -135.f)
	{
		return BequestGameplayTags::Character_Event_Hurt_Left;
	}
	else if (AngleDifference > 45.f && AngleDifference < 135.f)
	{
		return BequestGameplayTags::Character_Event_Hurt_Right;
	}
	else
	{
		return BequestGameplayTags::Character_Event_Hurt_Front;
	}
}