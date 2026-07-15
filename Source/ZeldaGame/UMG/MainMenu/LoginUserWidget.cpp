// Fill out your copyright notice in the Description page of Project Settings.


#include "LoginUserWidget.h"

#include "Components/EditableTextBox.h"
#include "Kismet/GameplayStatics.h"
#include "ZeldaGame/Data/Account/AccountSaveGame.h"
#include "ZeldaGame/ZeldaGame.h"

void ULoginUserWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (UGameplayStatics::DoesSaveGameExist(ZeldaGameSlots::AccountData, 0))
	{
		AccountSaveGame = Cast<UAccountSaveGame>(UGameplayStatics::LoadGameFromSlot(ZeldaGameSlots::AccountData, 0));
		if (AccountSaveGame)
		{
			AccountTextBox->SetText(FText::FromString(AccountSaveGame->Account));
			PasswordTextBox->SetText(FText::FromString(AccountSaveGame->Password));
			SaveCheckBox->SetCheckedState(ECheckBoxState::Checked);
		}
	}
}

void ULoginUserWidget::LoginGame()
{
	if (SaveCheckBox->IsChecked())
	{
		if (!AccountSaveGame)
		{
			AccountSaveGame = Cast<UAccountSaveGame>(UGameplayStatics::CreateSaveGameObject(UAccountSaveGame::StaticClass()));
		}
		AccountSaveGame->Account = AccountTextBox->GetText().ToString();
		AccountSaveGame->Password = PasswordTextBox->GetText().ToString();
		UGameplayStatics::SaveGameToSlot(AccountSaveGame, ZeldaGameSlots::AccountData, 0);
	}
	else
	{
		if (AccountSaveGame)
		{
			AccountSaveGame = nullptr;
			UGameplayStatics::DeleteGameInSlot(ZeldaGameSlots::AccountData, 0);
		}
	}
}