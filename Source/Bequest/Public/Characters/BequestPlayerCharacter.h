// Copyright Yooshley. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Characters/BequestCharacterBase.h"
#include "BequestPlayerCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;
class UInputMappingContext;
/**
 * 
 */
UCLASS(Blueprintable)
class BEQUEST_API ABequestPlayerCharacter : public ABequestCharacterBase
{
	GENERATED_BODY()
	
public:
	ABequestPlayerCharacter();

protected:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
private:
#pragma region Components
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Bequest|Camera", meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Bequest|Camera", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;
#pragma endregion

#pragma region Inputs
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Bequest|Input", meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* InputMappingContext;

	UFUNCTION(BlueprintCallable, Category = "Bequest|Input", meta = (AllowPrivateAccess = "true"))
	void Move(const FInputActionValue& InputActionValue);
#pragma endregion 
};
