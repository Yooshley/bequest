// Copyright Yooshley. All rights reserved.


#include "AbilitySystem/EffectCalculations/GEExecCalc_Damage.h"

#include "BequestGameplayTags.h"
#include "AbilitySystem/AttributeSets/BequestLifeAttributeSet.h"

struct FBequestDamageCapture
{
	DECLARE_ATTRIBUTE_CAPTUREDEF(Damage)

	FBequestDamageCapture()
	{
		DEFINE_ATTRIBUTE_CAPTUREDEF(UBequestLifeAttributeSet, Damage, Source, false);
	}
};


static FBequestDamageCapture GetDamageCapture()
{
	static FBequestDamageCapture DamageCapture;
	return DamageCapture;
}

UGEExecCalc_Damage::UGEExecCalc_Damage()
{
	RelevantAttributesToCapture.Add(GetDamageCapture().DamageDef);
}

void UGEExecCalc_Damage::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams,
	FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	const FGameplayEffectSpec EffectSpec = ExecutionParams.GetOwningSpec();

	FAggregatorEvaluateParameters EvaluateParams;
	EvaluateParams.SourceTags = EffectSpec.CapturedSourceTags.GetAggregatedTags();
	EvaluateParams.TargetTags = EffectSpec.CapturedTargetTags.GetAggregatedTags();

	float Damage = 0.f;
	for (const TPair<FGameplayTag, float>& TagMagnitude : EffectSpec.SetByCallerTagMagnitudes)
	{
		if (TagMagnitude.Key.MatchesTagExact(BequestGameplayTags::Shared_SetByCaller_Damage))
		{
			Damage = TagMagnitude.Value;
		}
	}

	if (Damage > 0.f)
	{
		OutExecutionOutput.AddOutputModifier(
			FGameplayModifierEvaluatedData(
				GetDamageCapture().DamageProperty,
				EGameplayModOp::Override,
				Damage
				)
			);
	}
}
