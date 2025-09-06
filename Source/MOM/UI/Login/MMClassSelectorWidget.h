// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MMClassSelectorWidget.generated.h"

class UButton;

UCLASS()
class MOM_API UMMClassSelectorWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
	TObjectPtr<UButton> WarriorButton;

	UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
	TObjectPtr<UButton> ArcherButton;

	UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
	TObjectPtr<UButton> WizardButton;

public:
	UMMClassSelectorWidget(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

protected:
	virtual void NativeConstruct() override;

private:
	UFUNCTION()
	void OnClickButton();
};
