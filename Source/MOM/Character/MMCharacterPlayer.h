// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/MMCharacterBase.h"
#include "GameplayTagContainer.h"
#include "Interface/MMComboWindowInterface.h"
#include "MMCharacterPlayer.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UMMInputData;
class UMMStateComponent;
class UMMCombatComponent;
struct FInputActionValue;

UCLASS()
class MOM_API AMMCharacterPlayer 
	: public AMMCharacterBase
	, public IMMComboWindowInterface
{
	GENERATED_BODY()

// Component
protected:
	UPROPERTY(VisibleAnywhere, Category = "Player | Component")
	TObjectPtr<UMMStateComponent> StateComp;

	UPROPERTY(VisibleAnywhere, Category = "Player | Component")
	TObjectPtr<UMMCombatComponent> CombatComp;

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

// Combo
protected:
	UPROPERTY(Replicated)
	bool bComboSequenceRunning;

	UPROPERTY(Replicated)
	bool bCanComboInput;

	UPROPERTY(Replicated)
	bool bSavedComboInput;

	UPROPERTY(Replicated)
	int32 ComboCounter;

	FTimerHandle ComboResetTimerHandle;

public:
	AMMCharacterPlayer();

public:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	/* IMMComboWindowInterface Implement*/
	virtual void EnableComboWindow() override;
	virtual void DisableComboWindow() override;
	virtual void AttackFinished(const float ComboResetDelay) override;

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

	FGameplayTag GetAttackPerform() const;

	bool CanPerformAttack(const FGameplayTag& AttackType);

	void ExecuteComboAttack(const FGameplayTag& AttackType);

	void DoAttack(const FGameplayTag& AttackType);

	void ResetCombo();

	/** 클라이언트가 서버에게 공격을 요청하는 RPC */
	UFUNCTION(Server, Reliable)
	void ServerRPC_RequestAttack(const FGameplayTag& AttackType);

	/** 서버가 모든 클라이언트에게 공격 애니메이션 재생을 지시하는 RPC */
	UFUNCTION(NetMulticast, Reliable)
	void MulticastRPC_PlayAttackMontage(UAnimMontage* PlayingMontage);
};
