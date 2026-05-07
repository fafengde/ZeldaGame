// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RegisterUserWidget.generated.h"

class UTextBlock;
class UButton;
/**
 * 
 */
UCLASS()
class ZELDAGAME_API URegisterUserWidget : public UUserWidget
{
	GENERATED_BODY()

protected:

	virtual void NativeConstruct() override;
	UFUNCTION()
	void OnSendCodeButtonClicked();
 
	void OnTimerCallback();

	void UpdateButtonText();
public:
	URegisterUserWidget(const FObjectInitializer& ObjectInitializer);
	
	protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton>SendCoudButton;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock>SendButtonTextBlock;
	UPROPERTY(EditAnywhere)
	int32 SendCodeButtonTime;
	int32 SendButtonCooldownTick;
};
