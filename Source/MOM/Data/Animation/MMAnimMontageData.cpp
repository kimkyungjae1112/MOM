// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/Animation/MMAnimMontageData.h"

UAnimMontage* UMMAnimMontageData::GetMontageForTag(const FGameplayTag& GroupTag, const int32 Index) const
{
	if (MontageGroupMap.Contains(GroupTag))
	{
		if (MontageGroupMap[GroupTag].Animations.Num() > Index && MontageGroupMap[GroupTag].Animations.Num() > 0)
		{
			return MontageGroupMap[GroupTag].Animations[Index];
		}
	}
	return nullptr;
}

UAnimMontage* UMMAnimMontageData::GetRandomMontageForTag(const FGameplayTag& GroupTag) const
{
	return nullptr;
}