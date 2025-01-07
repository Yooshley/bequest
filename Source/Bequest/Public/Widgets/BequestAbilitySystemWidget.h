// Copyright Yooshley. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BequestAbilitySystemWidget.generated.h"

struct FOnAttributeChangeData;
struct FGameplayAttribute;
class UAbilitySystemComponent;
/**
 * 
 */
UCLASS()
class BEQUEST_API UBequestAbilitySystemWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	bool ListenForLifeAttributeSetChanges = true;
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	bool ListenForGuardAttributeSetChanges = true;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	bool ListenForArmorAttributeSetChanges = true;
	
	UFUNCTION(BlueprintCallable, Category = "Ability System")
	bool InitializeAbilitySystemWidget(UAbilitySystemComponent* InOwnerAbilitySystemComponent);
	
	UFUNCTION(BlueprintCallable, BlueprintPure)
	UAbilitySystemComponent* GetOwnerAbilitySystemComponent() const;
	
	UFUNCTION(BlueprintImplementableEvent, Category = "Ability System")
	void On_MaximumLifeChanged(const float NewValue, const float OldValue, const float NewPercentage);

	UFUNCTION(BlueprintImplementableEvent, Category = "Ability System")
	void On_CurrentLifeChanged(const float NewValue, const float OldValue, const float NewPercentage);
	
	UFUNCTION(BlueprintImplementableEvent, Category = "Ability System")
	void On_MaximumGuardChanged(const float NewValue, const float OldValue, const float NewPercentage);
	
	UFUNCTION(BlueprintImplementableEvent, Category = "Ability System")
	void On_CurrentGuardChanged(const float NewValue, const float OldValue, const float NewPercentage);
	
	UFUNCTION(BlueprintImplementableEvent, Category = "Ability System")
	void On_GuardRegenerationChanged(const float NewValue, const float OldValue);

	UFUNCTION(BlueprintImplementableEvent, Category = "Ability System")
	void On_MaximumArmorChanged(const float NewValue, const float OldValue, const float NewPercentage);

	UFUNCTION(BlueprintImplementableEvent, Category = "Ability System")
	void On_CurrentArmorChanged(const float NewValue, const float OldValue, const float NewPercentage);
	
protected:
	TWeakObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
	
	FDelegateHandle MaximumLifeChangeDelegate;
	FDelegateHandle CurrentLifeChangeDelegate;
	FDelegateHandle MaximumGuardChangeDelegate;
	FDelegateHandle CurrentGuardChangeDelegate;
	FDelegateHandle GuardRegenerationChangeDelegate;
	FDelegateHandle MaximumArmorChangeDelegate;
	FDelegateHandle CurrentArmorChangeDelegate;
	
	void MaximumLifeChanged(const FOnAttributeChangeData& Data);
	
	void CurrentLifeChanged(const FOnAttributeChangeData& Data);
	
	void MaximumGuardChanged(const FOnAttributeChangeData& Data);
	
	void CurrentGuardChanged(const FOnAttributeChangeData& Data);
	
	void GuardRegenerationChanged(const FOnAttributeChangeData& Data);

	void MaximumArmorChanged(const FOnAttributeChangeData& Data);
	
	void CurrentArmorChanged(const FOnAttributeChangeData& Data);

	static void ResetDelegateHandle(FDelegateHandle DelegateHandle, UAbilitySystemComponent* OldAbilitySystemComponent, const FGameplayAttribute& Attribute);
};
