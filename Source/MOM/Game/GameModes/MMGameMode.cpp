// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/GameModes/MMGameMode.h"
#include "Game/State/MMGameState.h"
#include "GameFramework/PlayerStart.h"
#include "Player/MMPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Weapon/MMWeapon.h"
#include "Character/MMCharacterPlayer.h"
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

void AMMGameMode::SpawnSelectedCharacter(AController* PlayerController, TSubclassOf<AMMCharacterPlayer> SelectedCharacterClass)
{
	if (!PlayerController || !SelectedCharacterClass) return;

	if (AMMPlayerController* PC = Cast<AMMPlayerController>(PlayerController))
	{
		PC->ClientRPC_CloseCharacterSelectWidget();
	}

	TArray<AActor*> PlayerStarts;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerStart::StaticClass(), PlayerStarts);

	FTransform SpawnTransform;
	if (PlayerStarts.Num() > 0)
	{
		SpawnTransform = PlayerStarts[0]->GetActorTransform();
	}

	if (AMMCharacterPlayer* NewCharacter = GetWorld()->SpawnActor<AMMCharacterPlayer>(SelectedCharacterClass, SpawnTransform))
	{
		PlayerController->Possess(NewCharacter);

		FActorSpawnParameters SpawnParameter;
		SpawnParameter.Owner = NewCharacter;
		AMMWeapon* Weapon = GetWorld()->SpawnActor<AMMWeapon>(WeaponClass, SpawnParameter);
		Weapon->EquipItem();
	}
}
