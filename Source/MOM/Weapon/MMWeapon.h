// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon/MMWeaponBase.h"
#include "MMWeapon.generated.h"

UCLASS()
class MOM_API AMMWeapon : public AMMWeaponBase
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditAnywhere, Category = "Weapon | Socket")
	FName EquipSocket;

public:
	AMMWeapon();

public:
	virtual void EquipItem() override;

};
