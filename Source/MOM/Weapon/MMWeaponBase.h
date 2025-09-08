// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MMWeaponBase.generated.h"

UCLASS()
class MOM_API AMMWeaponBase : public AActor
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditAnywhere, Category = "Weapon | Mesh")
	TObjectPtr<UMeshComponent> MeshComp;

	UPROPERTY(EditAnywhere, Category = "Weapon | Mesh")
	TObjectPtr<UStaticMesh> MeshAsset;

public:	
	AMMWeaponBase();

public:
	virtual void OnConstruction(const FTransform& Transform) override;

	virtual void EquipItem();

	virtual void AttachToOwner(FName SocketName);

protected:
	virtual void BeginPlay() override;

};
