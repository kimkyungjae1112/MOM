// Fill out your copyright notice in the Description page of Project Settings.


#include "TEST/MMReplicateTestActor.h"
#include "Components/PointLightComponent.h"
#include "Net/UnrealNetwork.h"
//DOREPLIFETIME 매크로 저장 헤더 파일

AMMReplicateTestActor::AMMReplicateTestActor()
{
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh Comp"));
	MeshComp->SetupAttachment(RootComponent);

	PointLightComp = CreateDefaultSubobject<UPointLightComponent>(TEXT("Point Light Comp"));
	PointLightComp->SetupAttachment(RootComponent);
}

void AMMReplicateTestActor::BeginPlay()
{
	Super::BeginPlay();

}

void AMMReplicateTestActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	TimeLimit += DeltaTime;

	if (TimeLimit > 1.f)
	{
		TimeLimit = 0.f;

		if (HasAuthority())
		{
			ServerLightColor = FLinearColor(FMath::RandRange(0.0f, 1.0f), FMath::RandRange(0.0f, 1.0f), FMath::RandRange(0.0f, 1.0f), 1.0f);
			//PointLightComp->SetLightColor(ServerLightColor);
			//MulticastRPCChangeLightColor(ServerLightColor);
			OnRep_ServerLightColor();
		}
	}
}

void AMMReplicateTestActor::OnActorChannelOpen(FInBunch& InBunch, UNetConnection* Connection)
{
	// 채널이 열릴 때 호출되는 함수
	Super::OnActorChannelOpen(InBunch, Connection);
}

void AMMReplicateTestActor::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	// 이 속성이 바뀔 때, 콜백 함수를 호출할거에요~
	DOREPLIFETIME(AMMReplicateTestActor, ServerLightColor);
}

void AMMReplicateTestActor::OnRep_ServerLightColor()
{
	PointLightComp->SetLightColor(ServerLightColor);
}

void AMMReplicateTestActor::MulticastRPCChangeLightColor_Implementation(const FLinearColor& InColor)
{
	PointLightComp->SetLightColor(InColor);
}

