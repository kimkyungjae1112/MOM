// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/MMPlayerController.h"
#include "UI/Login/MMClassSelectorWidget.h"
#include "Game/GameModes/MMGameMode.h"
#include "Character/MMCharacterPlayer.h"
#include "MOM.h"

AMMPlayerController::AMMPlayerController()
{
}

void AMMPlayerController::PostInitializeComponents()
{
	MM_LOG(LogMMNetwork, Log, TEXT("%s"), TEXT("Begin"));

	Super::PostInitializeComponents();

	MM_LOG(LogMMNetwork, Log, TEXT("%s"), TEXT("End"));
}

void AMMPlayerController::PostNetInit()
{
	MM_LOG(LogMMNetwork, Log, TEXT("%s"), TEXT("Begin"));

	Super::PostNetInit();

	MM_LOG(LogMMNetwork, Log, TEXT("%s"), TEXT("End"));

}

void AMMPlayerController::BeginPlay()
{

	MM_LOG(LogMMNetwork, Log, TEXT("%s"), TEXT("Begin"));

	Super::BeginPlay();

	MM_LOG(LogMMNetwork, Log, TEXT("%s"), TEXT("End"));

	FInputModeUIOnly UIOnly;
	SetInputMode(UIOnly);
	bShowMouseCursor = true;
}

void AMMPlayerController::ClientRPC_ShowCharacterSelectWidget_Implementation()
{
	ClassSelectorWidget = CreateWidget<UMMClassSelectorWidget>(this, ClassSelectorWidgetClass);
	if (ClassSelectorWidget)
	{
		ClassSelectorWidget->AddToViewport();
	}
}

void AMMPlayerController::ClientRPC_CloseCharacterSelectWidget_Implementation()
{
	if (ClassSelectorWidget && ClassSelectorWidget->IsInViewport())
	{
		ClassSelectorWidget->RemoveFromParent();

		FInputModeGameOnly GameOnly;
		SetInputMode(GameOnly);
		bShowMouseCursor = false;
	}
}

bool AMMPlayerController::ServerRPC_RequestSpawnCharacter_Validate(TSubclassOf<AMMCharacterPlayer> SelectedCharacterClass)
{
	// SelectedCharacterClass != nullptr;
	return true;
}

void AMMPlayerController::ServerRPC_RequestSpawnCharacter_Implementation(TSubclassOf<AMMCharacterPlayer> SelectedCharacterClass)
{
	if (AMMGameMode* GM = Cast<AMMGameMode>(GetWorld()->GetAuthGameMode()))
	{
		GM->SpawnSelectedCharacter(this, SelectedCharacterClass);
	}
}