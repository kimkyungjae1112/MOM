// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/MMStateComponent.h"
#include "Net/UnrealNetwork.h"
#include "MOM.h"

UMMStateComponent::UMMStateComponent()
{
	SetIsReplicatedByDefault(true);
}

void UMMStateComponent::BeginPlay()
{
	Super::BeginPlay();

	
}

void UMMStateComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UMMStateComponent, CurrentState);
}

void UMMStateComponent::SetState(const FGameplayTag& NewState)
{
	// Server 에서 플레이어들의 상태를 변경한다.
	ServerRPC_SetState(NewState);
}

void UMMStateComponent::ClearPlayerState()
{
	SetState(FGameplayTag::EmptyTag);
}

bool UMMStateComponent::IsCurrentStateEqualToAny(const FGameplayTagContainer& TagsToCheck) const
{
	return TagsToCheck.HasTagExact(CurrentState);
}

bool UMMStateComponent::IsCurrentStateEqualToIt(const FGameplayTag& TagToCheck) const
{
	return TagToCheck == CurrentState;
}

void UMMStateComponent::OnRep_CurrentState()
{
	OnStateChanged();
}

bool UMMStateComponent::ServerRPC_SetState_Validate(const FGameplayTag& NewState)
{
	return CurrentState != MMGameplayTags::Character_State_Death;
}

void UMMStateComponent::ServerRPC_SetState_Implementation(const FGameplayTag& NewState)
{
	CurrentState = NewState;

	OnStateChanged();
}

void UMMStateComponent::OnStateChanged()
{
	if (CurrentState == MMGameplayTags::Character_State_Attacking)
	{
		bMovementInputEnabled = false;
	}
	else if (CurrentState == FGameplayTag::EmptyTag)
	{
		bMovementInputEnabled = true;
	}
}
