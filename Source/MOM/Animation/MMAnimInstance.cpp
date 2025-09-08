// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/MMAnimInstance.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/MMStateComponent.h"
#include "KismetAnimationLibrary.h"

void UMMAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	Character = Cast<ACharacter>(GetOwningActor());
	if (Character)
	{
		MovementComp = Character->GetCharacterMovement();
	}
}

void UMMAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (MovementComp)
	{
		Velocity = MovementComp->Velocity;
		GroundSpeed = Velocity.Size2D();
		bIsIdle = GroundSpeed < 3.f && MovementComp->GetCurrentAcceleration() == FVector::ZeroVector;
		bIsFalling = MovementComp->IsFalling();
		Direction = UKismetAnimationLibrary::CalculateDirection(Velocity, Character->GetActorRotation());

		FRotator ControlRot = Character->GetControlRotation();
		FRotator PlayerRot = Character->GetActorRotation();
		FRotator DeltaRot = (ControlRot - PlayerRot).GetNormalized();

		AimYaw = DeltaRot.Yaw;
		AimPitch = DeltaRot.Pitch;
	}
}

void UMMAnimInstance::AnimNotify_ResetPlayerState()
{
	if (UMMStateComponent* StateComp = Character->GetComponentByClass<UMMStateComponent>())
	{
		StateComp->ClearPlayerState();
	}
}

void UMMAnimInstance::AnimNotify_ResetAIState()
{
	if (UMMStateComponent* StateComp = Character->GetComponentByClass<UMMStateComponent>())
	{
		StateComp->ClearAIState();
	}
}
