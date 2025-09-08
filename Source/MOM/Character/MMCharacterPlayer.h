// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/MMCharacterBase.h"
#include "GameplayTagContainer.h"
#include "MMCharacterPlayer.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UMMInputData;
class UMMStateComponent;
struct FInputActionValue;

UCLASS()
class MOM_API AMMCharacterPlayer : public AMMCharacterBase
{
	GENERATED_BODY()

// Component
protected:
	UPROPERTY(VisibleAnywhere, Category = "Player | Component")
	TObjectPtr<UMMStateComponent> StateComp;

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

	UPROPERTY(EditAnywhere)
	TObjectPtr<UAnimMontage> TestAttackMontage;

public:
	AMMCharacterPlayer();

public:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	virtual void BeginPlay() override;
	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_Controller() override;
	void SetupInput() const;

// Util Input
private:
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);

// Attack Input
private:
	void DefaultAttack();

	UFUNCTION(Server, Reliable)
	void ServerRPC_Attack(UAnimMontage* InAttackMontage);

	UFUNCTION(NetMulticast, Reliable)
	void MulticastRPC_Attack(UAnimMontage* InAttackMontage);

	FGameplayTag GetAttackPerform() const;

	bool CanPerformAttack(const FGameplayTag& AttackType);

	void ExecuteComboAttack(const FGameplayTag& AttackType);

	void DoAttack(const FGameplayTag& AttackType);

	void ResetCombo();
};
