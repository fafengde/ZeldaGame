// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "KeySettingsWidget.generated.h"
class UScrollBox;
class UInputAction;
class UCustomKeyMapping;

//添加表头
USTRUCT()
struct FKeyInfoHeader : public FTableRowBase
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere)
	FText KeyDescribe;//按键描述
	UPROPERTY(EditAnywhere)
	FKey DefaultKey;//默认按键
	UPROPERTY(EditAnywhere)
	TObjectPtr<UInputAction> InputAction;
	
};

/**
 * 
 */
UCLASS()
class ZELDAGAME_API UKeySettingsWidget : public UUserWidget
{
	GENERATED_BODY()
protected:
	virtual void NativeOnInitialized() override;

	FKey GetCustomKey(FName KeyEventName);
	UFUNCTION(BlueprintCallable)
	void ResetAllKeys();

public:
	void SaveCustomKey(FName KeyEventName,FKey NewKey);//存入新按键
protected:
	UPROPERTY()
	TObjectPtr<UDataTable>KeyMappingDT;
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UScrollBox>KeyMappingScrollBox;
	UPROPERTY()
	TObjectPtr<UCustomKeyMapping> CustomKeyMapping;//存档的档案对象
};
