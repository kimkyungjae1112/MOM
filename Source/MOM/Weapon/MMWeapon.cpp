// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/MMWeapon.h"
#include "Data/Animation/MMAnimMontageData.h"

AMMWeapon::AMMWeapon()
{
	bReplicates = true;
}

void AMMWeapon::EquipItem()
{
	AttachToOwner(EquipSocket);
}

UAnimMontage* AMMWeapon::GetMontageForTag(const FGameplayTag& GroupTag, const int32 Index) const
{
	return MontageData->GetMontageForTag(GroupTag, Index);
}

UAnimMontage* AMMWeapon::GetMontageForRandom(const FGameplayTag& GroupTag) const
{
	return nullptr;
}
