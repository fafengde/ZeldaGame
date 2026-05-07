// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/CheckBox.h"
#include "LoginUserWidget.generated.h"

class UAccountSaveGame;
class UEditableTextBox;
class UCheckBox;
/**
 * 
 */
UCLASS()
class ZELDAGAME_API ULoginUserWidget : public UUserWidget
{
	GENERATED_BODY()
	protected:

	virtual void NativeConstruct() override;//第一次打开面板的时候需要读取
	
	UFUNCTION(BlueprintCallable)
	void LoginGame();


protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UEditableTextBox>AccountTextBox;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UEditableTextBox>PasswordTextBox;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UCheckBox>SaveCheckBox;
	UPROPERTY()
	TObjectPtr<UAccountSaveGame>AccountSaveGame;//用来存储的数据对象
};
