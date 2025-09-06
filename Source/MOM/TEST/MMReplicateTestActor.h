// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MMReplicateTestActor.generated.h"

class UPointLightComponent;

UCLASS()
class MOM_API AMMReplicateTestActor : public AActor
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> MeshComp;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UPointLightComponent> PointLightComp;

protected:
	UPROPERTY(ReplicatedUsing = OnRep_ServerLightColor)
	FLinearColor ServerLightColor;

protected:
	float TimeLimit = 0.f;

public:	
	AMMReplicateTestActor();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

public:
	virtual void OnActorChannelOpen(FInBunch& InBunch, UNetConnection* Connection) override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

protected:
	UFUNCTION()
	void OnRep_ServerLightColor();

	UFUNCTION(NetMulticast, Unreliable)
	void MulticastRPCChangeLightColor(const FLinearColor& InColor);
};
