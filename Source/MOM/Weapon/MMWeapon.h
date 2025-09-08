// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon/MMWeaponBase.h"
#include "GameplayTagContainer.h"
#include "MMWeapon.generated.h"

class UMMAnimMontageData;

UCLASS()
class MOM_API AMMWeapon : public AMMWeaponBase
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditAnywhere, Category = "Weapon | Socket")
	FName EquipSocket;

protected:
	UPROPERTY(EditAnywhere, Category = "Weapon | Data")
	TObjectPtr<UMMAnimMontageData> MontageData;

public:
	AMMWeapon();

public:
	virtual void EquipItem() override;

public:
	UAnimMontage* GetMontageForTag(const FGameplayTag& GroupTag, const int32 Index) const;
	UAnimMontage* GetMontageForRandom(const FGameplayTag& GroupTag) const;
};
