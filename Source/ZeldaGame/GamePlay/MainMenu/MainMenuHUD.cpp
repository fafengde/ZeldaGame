#include "MainMenuHUD.h"

#include "Blueprint/UserWidget.h"
#include "ZeldaGame/UMG/MainMenu/LoginUserWidget.h"
#include "ZeldaGame/UMG/MainMenu/MainMenuUserWidget.h"
#include "ZeldaGame/UMG/MainMenu/RegisterUserWidget.h"
#include "ZeldaGame/UMG/MainMenu/SettingsUserWidget.h"

void AMainMenuHUD::BeginPlay()
{
	Super::BeginPlay();

	CreateWidgetObjectPtr<UMainMenuUserWidget>(MainMenuUserWidget, TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/ZeldaGame/UMG/MainMenu/WBP_MainMenu.WBP_MainMenu_C'"));
	if (MainMenuUserWidget)
	{
		MainMenuUserWidget->AddToViewport();
		GetOwningPlayerController()->bShowMouseCursor = true;
	}
}

void AMainMenuHUD::ShowSettingsUI()
{
	CreateWidgetObjectPtr<USettingsUserWidget>(SettingsUserWidget, TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/ZeldaGame/UMG/MainMenu/WBP_Settings.WBP_Settings_C'"));
	if (SettingsUserWidget)
	{
		SettingsUserWidget->AddToViewport();
	}
}

void AMainMenuHUD::ShowLoginUI()
{
	CreateWidgetObjectPtr<ULoginUserWidget>(LoginUserWidget, TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/ZeldaGame/UMG/Login/WBP_Login.WBP_Login_C'"));
	if (LoginUserWidget)
	{
		LoginUserWidget->AddToViewport();
	}
}

void AMainMenuHUD::ShowRegisterUI()
{
	CreateWidgetObjectPtr<URegisterUserWidget>(RegisterUserWidget, TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/ZeldaGame/UMG/Login/WBP_Register.WBP_Register_C'"));
	if (RegisterUserWidget)
	{
		RegisterUserWidget->AddToViewport();
	}
}