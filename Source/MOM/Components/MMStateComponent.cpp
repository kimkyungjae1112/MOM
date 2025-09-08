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
	if (GetOwner()->HasAuthority())
	{
		CurrentState = NewState;
		OnStateChanged();
	}
	else
	{
		ServerRPC_SetState(NewState); 
	}
}

void UMMStateComponent::ClearPlayerState()
{
	if (GetOwner()->HasAuthority())
	{
		CurrentState = FGameplayTag::EmptyTag;
		OnStateChanged();
	}
}

void UMMStateComponent::ClearAIState()
{
	if (GetOwner()->HasAuthority())
	{
		CurrentState = FGameplayTag::EmptyTag;
	}
}

bool UMMStateComponent::IsCurrentStateEqualToAny(const FGameplayTagContainer& TagsToCheck) const
{
	return TagsToCheck.HasTagExact(CurrentState);
}

bool UMMStateComponent::IsCurrentStateEqualToIt(const FGameplayTag& TagToCheck) const
{
	return TagToCheck == CurrentState;
}

void UMMStateComponent::SetStateAndResetAfterDelay(const FGameplayTag& NewState, float Delay)
{
	if (GetOwner()->HasAuthority())
	{
		SetState(NewState);

		GetWorld()->GetTimerManager().ClearTimer(StateResetTimerHandle);
		GetWorld()->GetTimerManager().SetTimer(
			StateResetTimerHandle,
			this,
			&UMMStateComponent::ClearPlayerState,
			Delay,
			false
		);
	}
	else
	{
		ServerRPC_SetState(NewState);
	}
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
