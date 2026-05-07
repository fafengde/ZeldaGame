// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SettingsUserWidget.generated.h"

class UKeySettingsWidget;
/**
 * 
 */
UCLASS()
class ZELDAGAME_API USettingsUserWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	TObjectPtr<UKeySettingsWidget>GetKeySettingsWidget() const{return KeySettingsWidget;}
	
	protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UKeySettingsWidget>KeySettingsWidget;
	
};
