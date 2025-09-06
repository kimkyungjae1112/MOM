// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Login/MMClassSelectorWidget.h"
#include "Components/Button.h"
#include "Player/MMPlayerController.h"
#include "GameFramework/Character.h"
#include "MOM.h"

UMMClassSelectorWidget::UMMClassSelectorWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

void UMMClassSelectorWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if(WarriorButton) WarriorButton->OnClicked.AddDynamic(this, &ThisClass::OnClickButton);
	if(ArcherButton) ArcherButton->OnClicked.AddDynamic(this, &ThisClass::OnClickButton);
	if(WizardButton) WizardButton->OnClicked.AddDynamic(this, &ThisClass::OnClickButton);
}

void UMMClassSelectorWidget::OnClickButton()
{
	if (AMMPlayerController* PC = Cast<AMMPlayerController>(GetWorld()->GetFirstPlayerController()))
	{
		PC->Server_RequesSpawnCharacter(TSubclassOf<ACharacter>());
	}
}
