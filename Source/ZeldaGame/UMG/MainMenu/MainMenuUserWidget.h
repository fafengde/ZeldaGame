// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainMenuUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class ZELDAGAME_API UMainMenuUserWidget : public UUserWidget
{
	GENERATED_BODY()
protected:
	virtual void NativeConstruct() override;
	protected:
	UPROPERTY(meta = (BindWidgetAnim),Transient)
	TObjectPtr<UWidgetAnimation>MenuAnimation;
};
