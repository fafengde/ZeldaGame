// Fill out your copyright notice in the Description page of Project Settings.


#include "LoginUserWidget.h"

#include "Components/EditableTextBox.h"
#include "Kismet/GameplayStatics.h"
#include "ZeldaGame/Data/Account/AccountSaveGame.h"

#define ACCOUNT_DATA_SLOT TEXT("ACCOUNT_Slot")//自己的宏

void ULoginUserWidget::NativeConstruct()//第一次打开面板读取一次存档看是否有存档
{
	Super::NativeConstruct();
	//检查是否有过存档，如果有则读取并更新到UI中
	if (UGameplayStatics::DoesSaveGameExist(ACCOUNT_DATA_SLOT,0))
	{
		AccountSaveGame=Cast<UAccountSaveGame>(UGameplayStatics::LoadGameFromSlot(ACCOUNT_DATA_SLOT,0));
		AccountTextBox->SetText(FText::FromString(AccountSaveGame->Account));
		PasswordTextBox->SetText(FText::FromString(AccountSaveGame->Password));
		SaveCheckBox->SetCheckedState(ECheckBoxState::Checked);//将保存自动勾上
	}
	
}

void ULoginUserWidget::LoginGame()
{
	if (SaveCheckBox->IsChecked())//若保存按钮被按下
	{
		//存档
		if (!AccountSaveGame)
		{
			AccountSaveGame=Cast<UAccountSaveGame>(UGameplayStatics::CreateSaveGameObject(UAccountSaveGame::StaticClass()));
		}
		AccountSaveGame->Account=AccountTextBox->GetText().ToString();
		AccountSaveGame->Password=PasswordTextBox->GetText().ToString();
		//存档
		UGameplayStatics::SaveGameToSlot(AccountSaveGame,ACCOUNT_DATA_SLOT,0);
	}
	else
	{
		//不需要存档，删掉之前的存档
		if (AccountSaveGame)
		{
			AccountSaveGame=nullptr;//删除存档
			UGameplayStatics::DeleteGameInSlot(ACCOUNT_DATA_SLOT,0);
		}
	}
}


#undef ACCOUNT_DATA_SLOT//删除宏