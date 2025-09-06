// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/State/MMGameState.h"
#include "MOM.h"

void AMMGameState::HandleBeginPlay()
{
	MM_LOG(LogMMNetwork, Log, TEXT("%s"), TEXT("Begin"));

	Super::HandleBeginPlay();

	MM_LOG(LogMMNetwork, Log, TEXT("%s"), TEXT("End"));
}

void AMMGameState::OnRep_ReplicatedHasBegunPlay()
{
	MM_LOG(LogMMNetwork, Log, TEXT("%s"), TEXT("Begin"));

	Super::OnRep_ReplicatedHasBegunPlay();

	MM_LOG(LogMMNetwork, Log, TEXT("%s"), TEXT("End"));
}
