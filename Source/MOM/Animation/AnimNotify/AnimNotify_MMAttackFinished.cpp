// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/AnimNotify/AnimNotify_MMAttackFinished.h"
#include "Interface/MMComboWindowInterface.h"
UAnimNotify_MMAttackFinished::UAnimNotify_MMAttackFinished(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

void UAnimNotify_MMAttackFinished::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	if (AActor* Player = MeshComp->GetOwner())
	{
		if (IMMComboWindowInterface* Interface = Cast<IMMComboWindowInterface>(Player))
		{
			Interface->AttackFinished(ComboResetDelay);
		}
	}
}
