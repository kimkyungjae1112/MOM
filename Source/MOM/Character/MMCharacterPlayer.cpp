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
#include "GameplayTagContainer.h"
#include "MMGameplayTags.h"

AMMCharacterPlayer::AMMCharacterPlayer()
{
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
	check(StateComp);

	StateComp->SetStateAndResetAfterDelay(MMGameplayTags::Character_State_Attacking, 1.f);

	PlayAnimMontage(TestAttackMontage);

	ServerRPC_Attack(TestAttackMontage);
}

FGameplayTag AMMCharacterPlayer::GetAttackPerform() const
{
	return FGameplayTag();
}

bool AMMCharacterPlayer::CanPerformAttack(const FGameplayTag& AttackType)
{
	check(StateComp);

	FGameplayTagContainer Tags;
	Tags.AddTag(MMGameplayTags::Character_State_Attacking);
	Tags.AddTag(MMGameplayTags::Character_State_Stunned);

	return StateComp->IsCurrentStateEqualToAny(Tags) == false;
}

void AMMCharacterPlayer::ExecuteComboAttack(const FGameplayTag& AttackType)
{
}

void AMMCharacterPlayer::DoAttack(const FGameplayTag& AttackType)
{
}

void AMMCharacterPlayer::ResetCombo()
{
}

void AMMCharacterPlayer::ServerRPC_Attack_Implementation(UAnimMontage* InAttackMontage)
{
	MulticastRPC_Attack(InAttackMontage);
}

void AMMCharacterPlayer::MulticastRPC_Attack_Implementation(UAnimMontage* InAttackMontage)
{
	PlayAnimMontage(InAttackMontage);
}

