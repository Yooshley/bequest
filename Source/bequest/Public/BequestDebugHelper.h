#pragma once

namespace BequestDebug
{
	static void Print(const FString& Message, const FColor& Color = FColor::MakeRandomColor(), int32 Key = -1)
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(Key,7.f, Color, Message);
			UE_LOG(LogTemp, Warning, TEXT("%s"), *Message);
		}
	}

	static void Print(const FString& FloatTitle, float FloatValue, int32 Key = -1, const FColor& Color = FColor::MakeRandomColor())
	{
		if (GEngine)
		{
			const FString Message = FloatTitle + TEXT(": ") + FString::SanitizeFloat(FloatValue);
			GEngine->AddOnScreenDebugMessage(Key,7.f, Color, Message);
			UE_LOG(LogTemp, Warning, TEXT("%s"), *Message);
		}
	}
}