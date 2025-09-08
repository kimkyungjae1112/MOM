// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "MMComboWindowInterface.generated.h"

UINTERFACE(MinimalAPI)
class UMMComboWindowInterface : public UInterface
{
	GENERATED_BODY()
};

class MOM_API IMMComboWindowInterface
{
	GENERATED_BODY()

public:
	virtual void EnableComboWindow() = 0;
	virtual void DisableComboWindow() = 0;
	virtual void AttackFinished(const float ComboResetDelay) = 0;
};
