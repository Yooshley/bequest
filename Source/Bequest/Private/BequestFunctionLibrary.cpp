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
		return BequestGameplayTags::Shared_Status_Hurt_Front;
	}
	else if (AngleDifference <= -135.f || AngleDifference >= 135.f)
	{
		return BequestGameplayTags::Shared_Status_Hurt_Back;
	}
	else if (AngleDifference < -45.f && AngleDifference > -135.f)
	{
		return BequestGameplayTags::Shared_Status_Hurt_Left;
	}
	else if (AngleDifference > 45.f && AngleDifference < 135.f)
	{
		return BequestGameplayTags::Shared_Status_Hurt_Right;
	}
	else
	{
		return BequestGameplayTags::Shared_Status_Hurt_Front;
	}
}

void UBequestFunctionLibrary::SendGameplayEventToActorReplicated(AActor* SourceActor, AActor* TargetActor, FGameplayTag Tag, FGameplayEventData EventData)
{
	if (SourceActor->HasAuthority())
	{
		Multicast_SendGameplayEventToActor(TargetActor, Tag, EventData);
	}
	else
	{
		Server_SendGameplayEventToActor(TargetActor, Tag, EventData);
	}
}

void UBequestFunctionLibrary::Server_SendGameplayEventToActor_Implementation(AActor* TargetActor, FGameplayTag Tag, FGameplayEventData EventData)
{
	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(TargetActor, Tag, EventData);
}

void UBequestFunctionLibrary::Multicast_SendGameplayEventToActor_Implementation(AActor* TargetActor, FGameplayTag Tag, FGameplayEventData EventData)
{
	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(TargetActor, Tag, EventData);
}