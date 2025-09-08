// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/MMWeaponBase.h"
#include "GameFramework/Character.h"

AMMWeaponBase::AMMWeaponBase()
{
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh Comp"));
	SetRootComponent(MeshComp);
	MeshComp->SetCollisionProfileName(TEXT("NoCollision"));
}

void AMMWeaponBase::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	if (UStaticMeshComponent* StaticMeshComp = Cast<UStaticMeshComponent>(MeshComp))
	{
		StaticMeshComp->SetStaticMesh(MeshAsset);
	}
}

void AMMWeaponBase::EquipItem()
{
}

void AMMWeaponBase::AttachToOwner(FName SocketName)
{
	if (ACharacter* OwnerCharacter = Cast<ACharacter>(GetOwner()))
	{
		if (USkeletalMeshComponent* CharacterMesh = OwnerCharacter->GetMesh())
		{
			AttachToComponent(CharacterMesh, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), SocketName);
		}
	}
}

void AMMWeaponBase::BeginPlay()
{
	Super::BeginPlay();
	
}

