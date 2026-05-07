// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameFramework/HUD.h"
#include "MainMenuHUD.generated.h"

class ULoginUserWidget;
class USettingsUserWidget;
class UMainMenuUserWidget;
class URegisterUserWidget;
/**
 * 
 */
UCLASS()
class ZELDAGAME_API AMainMenuHUD : public AHUD
{
	GENERATED_BODY()
	protected:
	virtual void BeginPlay() override;
	UFUNCTION(BlueprintCallable)
	void ShowSettingsUI();
	UFUNCTION(BlueprintCallable)
	void ShowLoginUI();
	UFUNCTION(BlueprintCallable)
	void ShowRegisterUI();
	template<typename  T>
	void CreateWdgetObjectPtr(TObjectPtr<T>& ObjectPtr , const TCHAR*Path);
	
public:
	TObjectPtr<USettingsUserWidget> GetSettingsWidget() const {return SettingsUserWidget ;};//公开SettingsUserWidget让别人访问到它的控件
protected:
	UPROPERTY()
	TObjectPtr<UMainMenuUserWidget> MainMenuUserWidget;
	UPROPERTY()
	TObjectPtr<USettingsUserWidget> SettingsUserWidget;
	UPROPERTY()
	TObjectPtr<ULoginUserWidget>LoginUserWidget;
	UPROPERTY()
	TObjectPtr<URegisterUserWidget>RegisterUserWidget;
};

template <typename T>
void AMainMenuHUD::CreateWdgetObjectPtr(TObjectPtr<T>& ObjectPtr, const TCHAR* Path)
{
	if (ObjectPtr == nullptr)
	{
		TSubclassOf<T> WidgetClass=LoadClass<T>(nullptr,Path);
		ObjectPtr = CreateWidget<T>(GetOwningPlayerController(),WidgetClass);
	}
}
