// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameplayTagContainer.h"
#include "MMGameplayTags.h"
#include "MMStateComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MOM_API UMMStateComponent : public UActorComponent
{
	GENERATED_BODY()

protected:
	/* 이동키 입력 상태 관리 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State")
	bool bMovementInputEnabled = true;

	/* 캐릭터의 현재 상태 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, ReplicatedUsing = OnRep_CurrentState, Category = "State")
	FGameplayTag CurrentState;

public:
	UMMStateComponent();

protected:
	virtual void BeginPlay() override;

public:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

public:
	FORCEINLINE FGameplayTag GetCurrentState() const { return CurrentState; }
	FORCEINLINE bool bIsEnableMovement() const { return bMovementInputEnabled; }

public:
	/* 상태 설정 */
	void SetState(const FGameplayTag& NewState);

	/* 상태 초기화 */
	void ClearPlayerState();

	/* 현재 상태가 TagsToCheck 중에 있나? */
	bool IsCurrentStateEqualToAny(const FGameplayTagContainer& TagsToCheck) const;
	bool IsCurrentStateEqualToIt(const FGameplayTag& TagToCheck) const;

protected:
	UFUNCTION()
	void OnRep_CurrentState();

	UFUNCTION(Server, Reliable, WithValidation)
	void ServerRPC_SetState(const FGameplayTag& NewState);

protected:
	void OnStateChanged();
};
