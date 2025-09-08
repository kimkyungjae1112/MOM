// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "AnimNotify_MMAttackFinished.generated.h"

UCLASS()
class MOM_API UAnimNotify_MMAttackFinished : public UAnimNotify
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditAnywhere)
	float ComboResetDelay = 1.f;

public:
	UAnimNotify_MMAttackFinished(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;
};
