// Fill out your copyright notice in the Description page of Project Settings.


#include "KeyInfoWidget.h"

#include "KeySettingsWidget.h"
#include "SettingsUserWidget.h"
#include "Components/InputKeySelector.h"
#include "Components/PanelWidget.h"
#include "Components/TextBlock.h"
#include "ZeldaGame/GamePlay/MainMenu/MainMenuHUD.h"

void UKeyInfoWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	//绑定
	InputKeySelector->OnKeySelected.AddDynamic(this,&ThisClass::OnKeySelected);
}

void UKeyInfoWidget::OnKeySelected(FInputChord SelectedKey)
{
	//检查拾取新的按键和旧的按键是否相同，如果不相同则不存入
	if (CurrentKey==SelectedKey.Key)
	{
		return ;
	}
	//检查当前输入的按键是否被重复输入
	//检查其他与我一样的按键，然后检查是否有人已经使用我的按键
	//由于其他按键和我都添加进了相同的父容器中，所以，只要找到父容器，则可以找到其他按键
	for (int32  i=0;i <GetParent()->GetChildrenCount(); ++i)
	{
		//检查当前的KeyInfoWidget使用的控件，是否和我选的一样
		if (UKeyInfoWidget*KeyInfoWidget=Cast<UKeyInfoWidget>(GetParent()->GetChildAt(i)))
		{
			if (KeyInfoWidget->CurrentKey==SelectedKey.Key)
			{
				//修改当前按键为之前按键
				InputKeySelector->SetSelectedKey(CurrentKey);
				return ;
			}
		}
	}
	
	//如果不相同则存入
	if (AMainMenuHUD*Hud=Cast<AMainMenuHUD>(GetOwningPlayer()->GetHUD()))
	{
		Hud->GetSettingsWidget()->GetKeySettingsWidget()->SaveCustomKey(KeyEventName,SelectedKey.Key);//获取用户自定义的按键
	}
	
	CurrentKey=SelectedKey.Key;
}

void UKeyInfoWidget::InitPanel(const FName&InKeyEventName,const FText& KeyDescribe, FKey Key)
{
	KeyDescriptionTextBlock->SetText(KeyDescribe);
	InputKeySelector->SetSelectedKey(Key);

	KeyEventName=InKeyEventName;
	CurrentKey=Key;
}

void UKeyInfoWidget::ForceChangeKey(FKey NewKey)
{
	//强制将当前界面的按键设置成NewKey
	if (CurrentKey==NewKey)
	{
		return ;
	}
	CurrentKey=NewKey;//先设置当前Key
	InputKeySelector->SetSelectedKey(NewKey);//修改UI界面的Key
}
