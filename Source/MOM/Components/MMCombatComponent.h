// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameplayTagContainer.h"
#include "MMCombatComponent.generated.h"

class AMMWeapon;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MOM_API UMMCombatComponent : public UActorComponent
{
	GENERATED_BODY()

protected:
	UPROPERTY(ReplicatedUsing = OnRep_MainWeapon)
	TObjectPtr<AMMWeapon> MainWeapon;

	UPROPERTY(Replicated)
	FGameplayTag LastAttackType;

public:	
	UMMCombatComponent();

	FORCEINLINE AMMWeapon* GetMainWeapon() const { return MainWeapon; };
	FORCEINLINE FGameplayTag GetLastAttackType() const { return LastAttackType; };
	FORCEINLINE void SetLastAttackType(const FGameplayTag& InLastAttackType) { LastAttackType = InLastAttackType; };

public:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	void SetWeapon(AMMWeapon* InWeapon);

protected:
	virtual void BeginPlay() override;

protected:
	UFUNCTION()
	void OnRep_MainWeapon();
		
};
