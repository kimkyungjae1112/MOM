// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/GameModes/MMGameMode.h"
#include "Game/State/MMGameState.h"
#include "GameFramework/Character.h"
#include "Player/MMPlayerController.h"
#include "MOM.h"

AMMGameMode::AMMGameMode()
{
	GameStateClass = AMMGameState::StaticClass();
}

void AMMGameMode::StartPlay()
{
	MM_LOG(LogMMNetwork, Log, TEXT("%s"), TEXT("Begin"));

	Super::StartPlay();

	MM_LOG(LogMMNetwork, Log, TEXT("%s"), TEXT("End"));
}

void AMMGameMode::BeginPlay()
{
	MM_LOG(LogMMNetwork, Log, TEXT("%s"), TEXT("Begin"));

	Super::BeginPlay();

	MM_LOG(LogMMNetwork, Log, TEXT("%s"), TEXT("End"));
}


void AMMGameMode::PreLogin(const FString& Options, const FString& Address, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage)
{
	MM_LOG(LogMMNetwork, Log, TEXT("%s"), TEXT("============================================================"));
	MM_LOG(LogMMNetwork, Log, TEXT("%s"), TEXT("Begin"));

	Super::PreLogin(Options, Address, UniqueId, ErrorMessage);

	MM_LOG(LogMMNetwork, Log, TEXT("%s"), TEXT("End"));
}

APlayerController* AMMGameMode::Login(UPlayer* NewPlayer, ENetRole InRemoteRole, const FString& Portal, const FString& Options, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage)
{
	MM_LOG(LogMMNetwork, Log, TEXT("%s"), TEXT("Begin"));

	APlayerController* NewPlayerController = Super::Login(NewPlayer, InRemoteRole, Portal, Options, UniqueId, ErrorMessage);

	MM_LOG(LogMMNetwork, Log, TEXT("%s"), TEXT("End"));

	return NewPlayerController;
}

void AMMGameMode::PostLogin(APlayerController* NewPlayer)
{
	MM_LOG(LogMMNetwork, Log, TEXT("%s"), TEXT("Begin"));

	Super::PostLogin(NewPlayer);

	if (NewPlayer)
	{
		if (AMMPlayerController* PC = Cast<AMMPlayerController>(NewPlayer))
		{
			PC->ClientRPC_ShowCharacterSelectWidget();
		}
	}

	MM_LOG(LogMMNetwork, Log, TEXT("%s"), TEXT("End"));
}

void AMMGameMode::SpawnSelectedCharacter(AController* PlayerController, TSubclassOf<ACharacter> SelectedCharacterClass)
{
	if (PlayerController)
	{
		if (AMMPlayerController* PC = Cast<AMMPlayerController>(PlayerController))
		{
			PC->ClientRPC_CloseCharacterSelectWidget();
		}
	}
}
