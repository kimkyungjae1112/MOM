// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/MMCombatComponent.h"
#include "Net/UnrealNetwork.h"

UMMCombatComponent::UMMCombatComponent()
{
	SetIsReplicatedByDefault(true);
}


void UMMCombatComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UMMCombatComponent, MainWeapon);
	DOREPLIFETIME(UMMCombatComponent, LastAttackType);
}

void UMMCombatComponent::SetWeapon(AMMWeapon* InWeapon)
{
	MainWeapon = InWeapon;
}

void UMMCombatComponent::BeginPlay()
{
	Super::BeginPlay();

	
}

void UMMCombatComponent::OnRep_MainWeapon()
{
	UE_LOG(LogTemp, Display, TEXT("OnRep_MainWeapon"));
}



