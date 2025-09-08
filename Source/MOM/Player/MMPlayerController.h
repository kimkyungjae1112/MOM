// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MMPlayerController.generated.h"

class UMMClassSelectorWidget;
class AMMCharacterPlayer;

UCLASS()
class MOM_API AMMPlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(VisibleAnywhere, Category = "UI")
	TObjectPtr<UMMClassSelectorWidget> ClassSelectorWidget;

	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<UMMClassSelectorWidget> ClassSelectorWidgetClass;

public:
	AMMPlayerController();

protected:
	virtual void PostInitializeComponents() override;
	virtual void PostNetInit() override;
	virtual void BeginPlay() override;

public:
	UFUNCTION(Client, Reliable)
	void ClientRPC_ShowCharacterSelectWidget();

	UFUNCTION(Client, Reliable)
	void ClientRPC_CloseCharacterSelectWidget();

	UFUNCTION(Server, Reliable, WithValidation)
	void ServerRPC_RequestSpawnCharacter(TSubclassOf<AMMCharacterPlayer> SelectedCharacterClass);
	// AMMCharacterPlayer 바꾸자
};
