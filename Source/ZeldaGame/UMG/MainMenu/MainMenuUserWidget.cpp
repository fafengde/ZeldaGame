// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenuUserWidget.h"


void UMainMenuUserWidget::NativeConstruct()
{
	Super::NativeConstruct();
	PlayAnimation(MenuAnimation,0,1,EUMGSequencePlayMode::Forward,2.5f);
}
