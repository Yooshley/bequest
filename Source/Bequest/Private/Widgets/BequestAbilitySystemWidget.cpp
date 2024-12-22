// Copyright Yooshley. All rights reserved.


#include "Widgets/BequestAbilitySystemWidget.h"

#include "AbilitySystemComponent.h"
#include "BequestDebugHelper.h"
#include "AbilitySystem/AttributeSets/BequestArmorAttributeSet.h"
#include "AbilitySystem/AttributeSets/BequestGuardAttributeSet.h"
#include "AbilitySystem/AttributeSets/BequestLifeAttributeSet.h"

bool UBequestAbilitySystemWidget::InitializeAbilitySystemWidget(UAbilitySystemComponent* InOwnerAbilitySystemComponent)
{
	UAbilitySystemComponent* OldAbilitySystemComponent = AbilitySystemComponent.Get();
	
	AbilitySystemComponent = InOwnerAbilitySystemComponent;
	
	if (!GetOwnerAbilitySystemComponent())
	{
		return false;
	}

	// Reset bound old Attribute Change Delegates
	if (IsValid(OldAbilitySystemComponent))
	{
		ResetDelegateHandle(MaximumLifeChangeDelegate, OldAbilitySystemComponent, UBequestLifeAttributeSet::GetMaximumLifeAttribute());
		ResetDelegateHandle(CurrentLifeChangeDelegate, OldAbilitySystemComponent, UBequestLifeAttributeSet::GetCurrentLifeAttribute());
		ResetDelegateHandle(MaximumGuardChangeDelegate, OldAbilitySystemComponent, UBequestGuardAttributeSet::GetMaximumGuardAttribute());
		ResetDelegateHandle(CurrentGuardChangeDelegate, OldAbilitySystemComponent, UBequestGuardAttributeSet::GetCurrentGuardAttribute());
		ResetDelegateHandle(GuardRegenerationChangeDelegate, OldAbilitySystemComponent, UBequestGuardAttributeSet::GetGuardRegenerationAttribute());
		ResetDelegateHandle(MaximumArmorChangeDelegate, OldAbilitySystemComponent, UBequestArmorAttributeSet::GetMaximumArmorAttribute());
		ResetDelegateHandle(CurrentArmorChangeDelegate, OldAbilitySystemComponent, UBequestArmorAttributeSet::GetCurrentArmorAttribute());
	}

	// Bind Life Attribute Delegates
	if (ListenForLifeAttributeSetChanges)
	{
		if (AbilitySystemComponent->HasAttributeSetForAttribute(UBequestLifeAttributeSet::GetMaximumLifeAttribute()))
		{
			MaximumLifeChangeDelegate = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(UBequestLifeAttributeSet::GetMaximumLifeAttribute()).AddUObject(this, &UBequestAbilitySystemWidget::MaximumLifeChanged);
			CurrentLifeChangeDelegate = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(UBequestLifeAttributeSet::GetCurrentLifeAttribute()).AddUObject(this, &UBequestAbilitySystemWidget::CurrentLifeChanged);

			const float MaxLife = AbilitySystemComponent->GetNumericAttribute(UBequestLifeAttributeSet::GetMaximumLifeAttribute());
			const float CurrentLife = AbilitySystemComponent->GetNumericAttribute(UBequestLifeAttributeSet::GetCurrentLifeAttribute());
				
			// Blueprint Events to initialize the values
			On_MaximumLifeChanged(MaxLife, 0.0f, CurrentLife / MaxLife);
			On_CurrentLifeChanged(CurrentLife, 0.0f, CurrentLife / MaxLife);
		}
		else
		{
			return false;
		}
	}
	
	// Bind Guard Attribute Delegates
	if (ListenForGuardAttributeSetChanges)
	{
		if (AbilitySystemComponent->HasAttributeSetForAttribute(UBequestGuardAttributeSet::GetMaximumGuardAttribute()))
		{
			MaximumGuardChangeDelegate = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(UBequestGuardAttributeSet::GetMaximumGuardAttribute()).AddUObject(this, &UBequestAbilitySystemWidget::MaximumGuardChanged);
			CurrentGuardChangeDelegate = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(UBequestGuardAttributeSet::GetCurrentGuardAttribute()).AddUObject(this, &UBequestAbilitySystemWidget::CurrentGuardChanged);
			GuardRegenerationChangeDelegate = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(UBequestGuardAttributeSet::GetGuardRegenerationAttribute()).AddUObject(this, &UBequestAbilitySystemWidget::GuardRegenerationChanged);

			const float MaxGuard = AbilitySystemComponent->GetNumericAttribute(UBequestGuardAttributeSet::GetMaximumGuardAttribute());
			const float CurrentGuard = AbilitySystemComponent->GetNumericAttribute(UBequestGuardAttributeSet::GetCurrentGuardAttribute());
		
			// Blueprint Events to initialize the values
			On_MaximumGuardChanged(MaxGuard, 0.0f, CurrentGuard / MaxGuard);
			On_CurrentGuardChanged(CurrentGuard, 0.0f, CurrentGuard / MaxGuard);
			On_GuardRegenerationChanged(AbilitySystemComponent->GetNumericAttribute(UBequestGuardAttributeSet::GetGuardRegenerationAttribute()), 0.0f);
		}
		else
		{
			return false;
		}
	}

	// Bind Armor Attribute Delegates
	if (ListenForArmorAttributeSetChanges)
	{
		if (AbilitySystemComponent->HasAttributeSetForAttribute(UBequestArmorAttributeSet::GetMaximumArmorAttribute()))
		{
			MaximumArmorChangeDelegate = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(UBequestArmorAttributeSet::GetMaximumArmorAttribute()).AddUObject(this, &UBequestAbilitySystemWidget::MaximumArmorChanged);
			CurrentArmorChangeDelegate = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(UBequestArmorAttributeSet::GetCurrentArmorAttribute()).AddUObject(this, &UBequestAbilitySystemWidget::CurrentArmorChanged);

			const float MaxArmor = AbilitySystemComponent->GetNumericAttribute(UBequestArmorAttributeSet::GetMaximumArmorAttribute());
			const float CurrentArmor = AbilitySystemComponent->GetNumericAttribute(UBequestArmorAttributeSet::GetCurrentArmorAttribute());
				
			// Blueprint Events to initialize the values
			On_MaximumArmorChanged(MaxArmor, 0.0f, CurrentArmor / MaxArmor);
			On_CurrentArmorChanged(CurrentArmor, 0.0f, CurrentArmor / MaxArmor);
		}
		else
		{
			return false;
		}
	}
	
	return true;
}

UAbilitySystemComponent* UBequestAbilitySystemWidget::GetOwnerAbilitySystemComponent() const
{
	return AbilitySystemComponent.Get();
}

void UBequestAbilitySystemWidget::MaximumLifeChanged(const FOnAttributeChangeData& Data)
{
	const float CurrentLife = AbilitySystemComponent->GetNumericAttribute(UBequestLifeAttributeSet::GetCurrentLifeAttribute());
	On_MaximumLifeChanged(Data.NewValue, Data.OldValue, CurrentLife / Data.NewValue);
}

void UBequestAbilitySystemWidget::CurrentLifeChanged(const FOnAttributeChangeData& Data)
{
	const float MaxLife = AbilitySystemComponent->GetNumericAttribute(UBequestLifeAttributeSet::GetMaximumLifeAttribute());
	On_CurrentLifeChanged(Data.NewValue, Data.OldValue,  Data.NewValue / MaxLife);
}

void UBequestAbilitySystemWidget::MaximumGuardChanged(const FOnAttributeChangeData& Data)
{
	const float CurrentGuard = AbilitySystemComponent->GetNumericAttribute(UBequestGuardAttributeSet::GetCurrentGuardAttribute());
	On_MaximumGuardChanged(Data.NewValue, Data.OldValue, CurrentGuard / Data.NewValue);
}

void UBequestAbilitySystemWidget::CurrentGuardChanged(const FOnAttributeChangeData& Data)
{
	const float MaxGuard = AbilitySystemComponent->GetNumericAttribute(UBequestGuardAttributeSet::GetMaximumGuardAttribute());
	On_CurrentGuardChanged(Data.NewValue, Data.OldValue, Data.NewValue / MaxGuard);
}

void UBequestAbilitySystemWidget::GuardRegenerationChanged(const FOnAttributeChangeData& Data)
{
	On_GuardRegenerationChanged(Data.NewValue, Data.OldValue);
}

void UBequestAbilitySystemWidget::MaximumArmorChanged(const FOnAttributeChangeData& Data)
{
	const float CurrentArmor = AbilitySystemComponent->GetNumericAttribute(UBequestArmorAttributeSet::GetCurrentArmorAttribute());
	On_MaximumArmorChanged(Data.NewValue, Data.OldValue, CurrentArmor / Data.NewValue);
}

void UBequestAbilitySystemWidget::CurrentArmorChanged(const FOnAttributeChangeData& Data)
{
	const float MaximumArmor = AbilitySystemComponent->GetNumericAttribute(UBequestArmorAttributeSet::GetMaximumArmorAttribute());
	On_CurrentArmorChanged(Data.NewValue, Data.OldValue, Data.NewValue / MaximumArmor);
}

void UBequestAbilitySystemWidget::ResetDelegateHandle(FDelegateHandle DelegateHandle, UAbilitySystemComponent* OldAbilitySystemComponent, const FGameplayAttribute& Attribute)
{
	if (IsValid(OldAbilitySystemComponent))
	{
		OldAbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Attribute).Remove(DelegateHandle);
		DelegateHandle.Reset();
	}
}
