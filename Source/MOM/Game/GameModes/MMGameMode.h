// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MMGameMode.generated.h"

class AMMWeapon;
class AMMCharacterPlayer;

UCLASS()
class MOM_API AMMGameMode : public AGameModeBase
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, Category = "Weapon")
	TSubclassOf<AMMWeapon> WeaponClass;
	
public:
	AMMGameMode();

	virtual void StartPlay() override;
	virtual void BeginPlay() override;
	virtual void PreLogin(const FString& Options, const FString& Address, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage) override;
	virtual APlayerController* Login(UPlayer* NewPlayer, ENetRole InRemoteRole, const FString& Portal, const FString& Options, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage) override;
	virtual void PostLogin(APlayerController* NewPlayer) override;

public:
	void SpawnSelectedCharacter(AController* PlayerController, TSubclassOf<AMMCharacterPlayer> SelectedCharacterClass);
};
