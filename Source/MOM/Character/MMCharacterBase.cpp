// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/MMCharacterBase.h"

AMMCharacterBase::AMMCharacterBase()
{
	GetMesh()->SetRelativeLocation(FVector(0.f, 0.f, -88.f));
	GetMesh()->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));
}

void AMMCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}


