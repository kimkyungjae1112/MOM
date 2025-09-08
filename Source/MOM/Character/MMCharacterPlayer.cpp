// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/MMCharacterPlayer.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/PlayerController.h"
#include "Camera/CameraComponent.h"
#include "Data/Input/MMInputData.h"
#include "Components/MMStateComponent.h"
#include "Components/MMCombatComponent.h"
#include "Weapon/MMWeapon.h"
#include "Net/UnrealNetwork.h"

#include "GameplayTagContainer.h"
#include "MMGameplayTags.h"

AMMCharacterPlayer::AMMCharacterPlayer()
{
	bReplicates = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm Comp"));
	SpringArmComp->SetupAttachment(RootComponent);
	SpringArmComp->bUsePawnControlRotation = true;

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera Comp"));
	CameraComp->SetupAttachment(SpringArmComp);
	CameraComp->bUsePawnControlRotation = false;

	StateComp = CreateDefaultSubobject<UMMStateComponent>(TEXT("State Comp"));
	CombatComp = CreateDefaultSubobject<UMMCombatComponent>(TEXT("Combat Comp"));
}

void AMMCharacterPlayer::BeginPlay()
{
	Super::BeginPlay();
}

void AMMCharacterPlayer::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	SetupInput();
}

void AMMCharacterPlayer::OnRep_Controller()
{
	Super::OnRep_Controller();

	SetupInput();
}

void AMMCharacterPlayer::SetupInput() const
{
	if (APlayerController* PC = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer()))
		{
			Subsystem->ClearAllMappings();
			Subsystem->AddMappingContext(InputData->IMC_Default, 0);
		}
	}
}

void AMMCharacterPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(InputData->IA_Move, ETriggerEvent::Triggered, this, &ThisClass::Move);
		EnhancedInputComponent->BindAction(InputData->IA_Look, ETriggerEvent::Triggered, this, &ThisClass::Look);
		EnhancedInputComponent->BindAction(InputData->IA_DefaultAttack, ETriggerEvent::Started, this, &ThisClass::DefaultAttack);
	}
}

void AMMCharacterPlayer::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AMMCharacterPlayer, bComboSequenceRunning);
	DOREPLIFETIME(AMMCharacterPlayer, bCanComboInput);
	DOREPLIFETIME(AMMCharacterPlayer, bSavedComboInput);
	DOREPLIFETIME(AMMCharacterPlayer, ComboCounter);
}

void AMMCharacterPlayer::EnableComboWindow()
{
	bCanComboInput = true;
}

void AMMCharacterPlayer::DisableComboWindow()
{
	check(CombatComp);

	bCanComboInput = false;

	if (bSavedComboInput)
	{
		bSavedComboInput = false;
		ComboCounter++;
		DoAttack(CombatComp->GetLastAttackType());
	}
}

void AMMCharacterPlayer::AttackFinished(const float ComboResetDelay)
{
	check(StateComp);

	StateComp->ClearPlayerState();

	// ComboResetDelay 후에 콤보 시퀀스 완전 종료
	GetWorld()->GetTimerManager().SetTimer(ComboResetTimerHandle, this, &ThisClass::ResetCombo, ComboResetDelay, false);
}

void AMMCharacterPlayer::Move(const FInputActionValue& Value)
{
	check(StateComp);
	if (!StateComp->bIsEnableMovement()) return;

	FVector2D InputValue = Value.Get<FVector2D>();

	const FRotator Rotation = Controller->GetControlRotation();
	const FRotator YawRotation = FRotator(0.f, Rotation.Yaw, 0.f);

	const FVector ForwardVector = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightVector = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	AddMovementInput(ForwardVector, InputValue.X);
	AddMovementInput(RightVector, InputValue.Y);
}

void AMMCharacterPlayer::Look(const FInputActionValue& Value)
{
	FVector2D InputValue = Value.Get<FVector2D>();

	AddControllerPitchInput(-1.f * InputValue.Y);
	AddControllerYawInput(InputValue.X);
}

void AMMCharacterPlayer::DefaultAttack()
{
	FGameplayTag AttackType = MMGameplayTags::Character_Attack_Light;

	ServerRPC_RequestAttack(AttackType);
}

FGameplayTag AMMCharacterPlayer::GetAttackPerform() const
{
	return FGameplayTag();
}

bool AMMCharacterPlayer::CanPerformAttack(const FGameplayTag& AttackType)
{
	check(StateComp);

	FGameplayTagContainer MMTags;
	MMTags.AddTag(MMGameplayTags::Character_State_Stunned);

	return StateComp->IsCurrentStateEqualToAny(MMTags) == false;
}

void AMMCharacterPlayer::ExecuteComboAttack(const FGameplayTag& AttackType)
{
	check(StateComp);

	if (StateComp->GetCurrentState() != MMGameplayTags::Character_State_Attacking)
	{
		if (bComboSequenceRunning && bCanComboInput == false)
		{
			ComboCounter++;
		}
		else
		{
			ResetCombo();
			bComboSequenceRunning = true;
		}

		DoAttack(AttackType);

		GetWorld()->GetTimerManager().ClearTimer(ComboResetTimerHandle);
	}
	else if (bCanComboInput)
	{
		bSavedComboInput = true;
	}
}

void AMMCharacterPlayer::DoAttack(const FGameplayTag& AttackType)
{
	check(CombatComp);
	check(StateComp);

	if (AMMWeapon* Weapon = CombatComp->GetMainWeapon())
	{
		StateComp->SetState(MMGameplayTags::Character_State_Attacking);

		CombatComp->SetLastAttackType(AttackType);

		UAnimMontage* Montage = Weapon->GetMontageForTag(AttackType, ComboCounter);
		if (!Montage)
		{
			ComboCounter = 0;
			Montage = Weapon->GetMontageForTag(AttackType, ComboCounter);
		}

		if (Montage)
		{
			MulticastRPC_PlayAttackMontage(Montage);
		}
	}
}

void AMMCharacterPlayer::ResetCombo()
{
	bComboSequenceRunning = false;
	bCanComboInput = false;
	bSavedComboInput = false;
	ComboCounter = 0;
}

void AMMCharacterPlayer::ServerRPC_RequestAttack_Implementation(const FGameplayTag& AttackType)
{
	if (CanPerformAttack(AttackType))
	{
		ExecuteComboAttack(AttackType);
	}
}

void AMMCharacterPlayer::MulticastRPC_PlayAttackMontage_Implementation(UAnimMontage* PlayingMontage)
{
	PlayAnimMontage(PlayingMontage);
}