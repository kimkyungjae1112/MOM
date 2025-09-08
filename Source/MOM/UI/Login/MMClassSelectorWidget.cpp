// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Login/MMClassSelectorWidget.h"
#include "Components/Button.h"
#include "Player/MMPlayerController.h"
#include "Character/MMCharacterPlayer.h"
#include "MOM.h"

UMMClassSelectorWidget::UMMClassSelectorWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

void UMMClassSelectorWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if(WarriorButton) WarriorButton->OnClicked.AddDynamic(this, &ThisClass::OnClickWarriorButton);
	if(ArcherButton) ArcherButton->OnClicked.AddDynamic(this, &ThisClass::OnClickArcherButton);
	if(WizardButton) WizardButton->OnClicked.AddDynamic(this, &ThisClass::OnClickWizardButton);
}

void UMMClassSelectorWidget::OnClickWarriorButton()
{
	if (AMMPlayerController* PC = Cast<AMMPlayerController>(GetWorld()->GetFirstPlayerController()))
	{
		PC->ServerRPC_RequestSpawnCharacter(WarriorPlayerClass);
	}
}

void UMMClassSelectorWidget::OnClickArcherButton()
{
	if (AMMPlayerController* PC = Cast<AMMPlayerController>(GetWorld()->GetFirstPlayerController()))
	{
		PC->ServerRPC_RequestSpawnCharacter(ArcherPlayerClass);
	}
}

void UMMClassSelectorWidget::OnClickWizardButton()
{
	if (AMMPlayerController* PC = Cast<AMMPlayerController>(GetWorld()->GetFirstPlayerController()))
	{
		PC->ServerRPC_RequestSpawnCharacter(WizardPlayerClass);
	}
}
