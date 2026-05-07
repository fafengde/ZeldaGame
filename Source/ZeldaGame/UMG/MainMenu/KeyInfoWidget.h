// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "KeyInfoWidget.generated.h"

class UInputKeySelector;
class UTextBlock;
/**
 * 
 */
UCLASS()
class ZELDAGAME_API UKeyInfoWidget : public UUserWidget
{
	GENERATED_BODY()
protected:
	
	virtual void NativeOnInitialized() override;
	UFUNCTION()
	void OnKeySelected(FInputChord SelectedKey);
public:
	
	void InitPanel(const FName&InKeyEventName,const FText& KeyDescribe,FKey Key);

	FName GetKeyEventName()const{return KeyEventName; }//公开按键名称

	void ForceChangeKey(FKey NewKey);//强制设定新按键
protected:
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> KeyDescriptionTextBlock;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UInputKeySelector> InputKeySelector;

	FName KeyEventName;//存按键名称
	FKey CurrentKey;//拾取当前按键
};
