// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/MMCharacterBase.h"
#include "MMCharacterPlayer.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UMMInputData;
struct FInputActionValue;

UCLASS()
class MOM_API AMMCharacterPlayer : public AMMCharacterBase
{
	GENERATED_BODY()

// Camera
protected:
	UPROPERTY(VisibleAnywhere, Category = "Player | Camera")
	TObjectPtr<USpringArmComponent> SpringArmComp;

	UPROPERTY(VisibleAnywhere, Category = "Player | Camera")
	TObjectPtr<UCameraComponent> CameraComp;

// Input
protected:
	UPROPERTY(EditAnywhere, Category = "Player | Input")
	TObjectPtr<UMMInputData> InputData;

public:
	AMMCharacterPlayer();

protected:
	virtual void BeginPlay() override;

public:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
};
