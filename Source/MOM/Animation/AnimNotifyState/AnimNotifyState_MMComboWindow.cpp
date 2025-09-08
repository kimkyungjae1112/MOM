// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/AnimNotifyState/AnimNotifyState_MMComboWindow.h"
#include "Interface/MMComboWindowInterface.h"

UAnimNotifyState_MMComboWindow::UAnimNotifyState_MMComboWindow(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

void UAnimNotifyState_MMComboWindow::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);

	if (AActor* Player = MeshComp->GetOwner())
	{
		if (IMMComboWindowInterface* Interface = Cast<IMMComboWindowInterface>(Player))
		{
			Interface->EnableComboWindow();
		}
	}
	
}

void UAnimNotifyState_MMComboWindow::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);

	if (AActor* Player = MeshComp->GetOwner())
	{
		if (IMMComboWindowInterface* Interface = Cast<IMMComboWindowInterface>(Player))
		{
			Interface->DisableComboWindow();
		}
	}
}
