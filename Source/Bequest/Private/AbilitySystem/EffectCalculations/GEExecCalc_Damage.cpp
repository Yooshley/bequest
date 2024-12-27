// Copyright Yooshley. All rights reserved.


#include "AbilitySystem/EffectCalculations/GEExecCalc_Damage.h"

#include "BequestGameplayTags.h"
#include "AbilitySystem/AttributeSets/BequestArmorAttributeSet.h"
#include "AbilitySystem/AttributeSets/BequestGuardAttributeSet.h"
#include "AbilitySystem/AttributeSets/BequestLifeAttributeSet.h"

struct FBequestDamageCapture
{
	DECLARE_ATTRIBUTE_CAPTUREDEF(LifeDamage)
	DECLARE_ATTRIBUTE_CAPTUREDEF(ArmorDamage)
	DECLARE_ATTRIBUTE_CAPTUREDEF(GuardDamage)

	FBequestDamageCapture()
	{
		DEFINE_ATTRIBUTE_CAPTUREDEF(UBequestLifeAttributeSet, LifeDamage, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UBequestArmorAttributeSet, ArmorDamage, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UBequestGuardAttributeSet, GuardDamage, Source, false);
	}
};


static FBequestDamageCapture GetDamageCapture()
{
	static FBequestDamageCapture DamageCapture;
	return DamageCapture;
}

UGEExecCalc_Damage::UGEExecCalc_Damage()
{
	RelevantAttributesToCapture.Add(GetDamageCapture().LifeDamageDef);
	RelevantAttributesToCapture.Add(GetDamageCapture().ArmorDamageDef);
	RelevantAttributesToCapture.Add(GetDamageCapture().GuardDamageDef);
}

void UGEExecCalc_Damage::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams,
	FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	const FGameplayEffectSpec EffectSpec = ExecutionParams.GetOwningSpec();

	FAggregatorEvaluateParameters EvaluateParams;
	EvaluateParams.SourceTags = EffectSpec.CapturedSourceTags.GetAggregatedTags();
	EvaluateParams.TargetTags = EffectSpec.CapturedTargetTags.GetAggregatedTags();

	float Damage = 0.f;
	FProperty* DamageType = nullptr;
	for (const TPair<FGameplayTag, float>& TagMagnitude : EffectSpec.SetByCallerTagMagnitudes)
	{
		if (TagMagnitude.Key.MatchesTagExact(BequestGameplayTags::Character_SetByCaller_Damage_Life))
		{
			Damage = TagMagnitude.Value;
			DamageType = GetDamageCapture().LifeDamageProperty;
		}
		if (TagMagnitude.Key.MatchesTagExact(BequestGameplayTags::Character_SetByCaller_Damage_Armor))
		{
			Damage = TagMagnitude.Value;
			DamageType = GetDamageCapture().ArmorDamageProperty;
		}
		if (TagMagnitude.Key.MatchesTagExact(BequestGameplayTags::Character_SetByCaller_Damage_Guard))
		{
			Damage = TagMagnitude.Value;
			DamageType = GetDamageCapture().GuardDamageProperty;
		}
	}

	if (Damage > 0.f)
	{
		OutExecutionOutput.AddOutputModifier(
			FGameplayModifierEvaluatedData(
				DamageType,
				EGameplayModOp::Override,
				Damage
				)
			);
	}
}
