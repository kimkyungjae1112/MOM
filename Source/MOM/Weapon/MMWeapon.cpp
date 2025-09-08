// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/MMWeapon.h"

AMMWeapon::AMMWeapon()
{
	bReplicates = true;
}

void AMMWeapon::EquipItem()
{
	AttachToOwner(EquipSocket);
}
