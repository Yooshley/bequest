// Copyright Yooshley. All rights reserved.


#include "AbilitySystem/EffectCalculations/GEExecCalc_Damage.h"

#include "BequestGameplayTags.h"
#include "AbilitySystem/AttributeSets/BequestArmorAttributeSet.h"
#include "AbilitySystem/AttributeSets/BequestGuardAttributeSet.h"
#include "AbilitySystem/AttributeSets/BequestLifeAttributeSet.h"

struct FBequestDamageCapture
{
	DECLARE_ATTRIBUTE_CAPTUREDEF(FinalLifeDamage)
	DECLARE_ATTRIBUTE_CAPTUREDEF(FinalArmorDamage)
	DECLARE_ATTRIBUTE_CAPTUREDEF(FinalGuardDamage)

	FBequestDamageCapture()
	{
		DEFINE_ATTRIBUTE_CAPTUREDEF(UBequestLifeAttributeSet, FinalLifeDamage, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UBequestArmorAttributeSet, FinalArmorDamage, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UBequestGuardAttributeSet, FinalGuardDamage, Source, false);
	}
};


static FBequestDamageCapture GetDamageCapture()
{
	static FBequestDamageCapture DamageCapture;
	return DamageCapture;
}

UGEExecCalc_Damage::UGEExecCalc_Damage()
{
	RelevantAttributesToCapture.Add(GetDamageCapture().FinalLifeDamageDef);
	RelevantAttributesToCapture.Add(GetDamageCapture().FinalArmorDamageDef);
	RelevantAttributesToCapture.Add(GetDamageCapture().FinalGuardDamageDef);
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
			DamageType = GetDamageCapture().FinalLifeDamageProperty;
		}
		if (TagMagnitude.Key.MatchesTagExact(BequestGameplayTags::Character_SetByCaller_Damage_Armor))
		{
			Damage = TagMagnitude.Value;
			DamageType = GetDamageCapture().FinalArmorDamageProperty;
		}
		if (TagMagnitude.Key.MatchesTagExact(BequestGameplayTags::Character_SetByCaller_Damage_Guard))
		{
			Damage = TagMagnitude.Value;
			DamageType = GetDamageCapture().FinalGuardDamageProperty;
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
