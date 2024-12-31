// Copyright Yooshley. All rights reserved.


#include "Game/BequestGameMode.h"
#include "Characters/BequestPlayerCharacter.h"
#include "GameFramework/GameUserSettings.h"

ABequestGameMode::ABequestGameMode()
{
	UGameUserSettings* UserSettings = GEngine ? GEngine->GetGameUserSettings() : nullptr;
	if (UserSettings)
	{
		UserSettings->SetFullscreenMode(EWindowMode::Windowed);
		const FIntPoint Resolution(1280, 800);
		UserSettings->SetScreenResolution(Resolution);
		UserSettings->ApplySettings(false);
	}
}

void ABequestGameMode::OnPostLogin(AController* NewPlayer)
{
	Super::OnPostLogin(NewPlayer);
	int8 NewPlayerIndex = PlayerArray.AddUnique(NewPlayer);

	APlayerController* PlayerController = Cast<APlayerController>(NewPlayer);
	if (PlayerController)
	{
		PlayerController->GetOnNewPawnNotifier().AddLambda([this, NewPlayerIndex](APawn* NewPawn)
		{
			ABequestPlayerCharacter* PlayerCharacter = Cast<ABequestPlayerCharacter>(NewPawn);
			if (PlayerCharacter)
			{
				PlayerCharacter->EquipmentColorIndex = NewPlayerIndex;
				PlayerCharacter->SetEquipmentColor(NewPlayerIndex);
			}
		});
	}
}
