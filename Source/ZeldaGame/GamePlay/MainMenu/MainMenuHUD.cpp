 // Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenuHUD.h"

#include "NavigationSystemTypes.h"
#include "Blueprint/UserWidget.h"
#include "ZeldaGame/UMG/MainMenu/LoginUserWidget.h"
#include "ZeldaGame/UMG/MainMenu/MainMenuUserWidget.h"
#include "ZeldaGame/UMG/MainMenu/RegisterUserWidget.h"
#include "ZeldaGame/UMG/MainMenu/SettingsUserWidget.h"

#define CREATE_WIDGET_OBJECT(Objectptr,ObjectClass,Path)if (!Objectptr)\
	{\
		TSubclassOf<ObjectClass>WidgetClass=LoadClass<ObjectClass>(nullptr,TEXT(Path));\
		Objectptr=CreateWidget<ObjectClass>(GetOwningPlayerController(),WidgetClass);\
	}

void AMainMenuHUD::BeginPlay()
{
	Super::BeginPlay();
	//游戏开始加载类
	TSubclassOf<UMainMenuUserWidget> WidgetClass=LoadClass<UMainMenuUserWidget>(nullptr,TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/ZeldaGame/UMG/MainMenu/WBP_MainMenu.WBP_MainMenu_C'"));
	if (WidgetClass)
	{
		//通过类实例对象
		MainMenuUserWidget=CreateWidget<UMainMenuUserWidget>(GetOwningPlayerController(),WidgetClass);
		if (MainMenuUserWidget)//检测是否有效
		{      
			MainMenuUserWidget->AddToViewport();
		}
		GetOwningPlayerController()->bShowMouseCursor=true;
	}
}

void AMainMenuHUD::ShowSettingsUI()
{
	if (!SettingsUserWidget)
	{
		//TSubclassOf<USettingsUserWidget> WidgetClass=LoadClass<USettingsUserWidget>(nullptr,TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/ZeldaGame/UMG/MainMenu/WBP_Settings.WBP_Settings_C'"));///Script/UMGEditor.WidgetBlueprint'/Game/ZeldaGame/UMG/MainMenu/Second/WBP_Settings2.WBP_Settings2'
		TSubclassOf<USettingsUserWidget> WidgetClass=LoadClass<USettingsUserWidget>(nullptr,TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/ZeldaGame/UMG/MainMenu/WBP_Settings.WBP_Settings_C'"));///Script/UMGEditor.WidgetBlueprint'/Game/ZeldaGame/UMG/MainMenu/Second/WBP_Settings2.WBP_Settings2'
		
		SettingsUserWidget=CreateWidget<USettingsUserWidget>(GetOwningPlayerController(),WidgetClass);
	}
	if (SettingsUserWidget)
	{
		SettingsUserWidget->AddToViewport();
	}
}

 void AMainMenuHUD::ShowLoginUI()
 {
	// if (!LoginUserWidget)
	// {
	// 	TSubclassOf<ULoginUserWidget>WidgetClass=LoadClass<ULoginUserWidget>(nullptr,TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/ZeldaGame/UMG/Login/WBP_Login.WBP_Login_C'"));
	// 	LoginUserWidget=CreateWidget<ULoginUserWidget>(GetOwningPlayerController(),WidgetClass);
	// }
	CreateWdgetObjectPtr<ULoginUserWidget>(LoginUserWidget,TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/ZeldaGame/UMG/Login/WBP_Login.WBP_Login_C'"));
	if (LoginUserWidget)
	{
		LoginUserWidget->AddToViewport();
	}
 }

 void AMainMenuHUD::ShowRegisterUI()
 {
	CREATE_WIDGET_OBJECT(RegisterUserWidget,URegisterUserWidget,"/Script/UMGEditor.WidgetBlueprint'/Game/ZeldaGame/UMG/Login/WBP_Register.WBP_Register_C'");
	if (RegisterUserWidget)
	{
		RegisterUserWidget->AddToViewport();
	}
 }
#undef CREATE_WIDGET_OBJECT