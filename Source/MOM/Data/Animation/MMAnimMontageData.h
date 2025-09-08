// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GameplayTagContainer.h"
#include "MMAnimMontageData.generated.h"

USTRUCT(BlueprintType)
struct FMMMontageGroup
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<UAnimMontage*> Animations;
};

UCLASS()
class MOM_API UMMAnimMontageData : public UPrimaryDataAsset
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName = "Montage Groups")
	TMap<FGameplayTag, FMMMontageGroup> MontageGroupMap;

public:
	UAnimMontage* GetMontageForTag(const FGameplayTag& GroupTag, const int32 Index) const;
	UAnimMontage* GetRandomMontageForTag(const FGameplayTag& GroupTag) const;
	
};
