// Fill out your copyright notice in the Description page of Project Settings.


#include "KeySettingsWidget.h"

#include "KeyInfoWidget.h"
#include "Components/ScrollBox.h"
#include "Kismet/GameplayStatics.h"
#include "ZeldaGame/ZeldaGame.h"
#include "ZeldaGame/Data/KeyMapping/CustomKeyMapping.h"

void UKeySettingsWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	KeyMappingDT = LoadObject<UDataTable>(this, TEXT("/Script/Engine.DataTable'/Game/ZeldaGame/Data/DT_KeyMapping.DT_KeyMapping'"));
	if (!KeyMappingDT)
	{
		return;
	}

	TSubclassOf<UKeyInfoWidget> WidgetClass = LoadClass<UKeyInfoWidget>(nullptr, TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/ZeldaGame/UMG/MainMenu/WBP_KeyInfo.WBP_KeyInfo_C'"));
	if (!WidgetClass)
	{
		return;
	}

	// 使用 GetRowNames + FindRow 替代 GetRowMap + reinterpret_cast
	// DataTable::FindRow 是类型安全的，不需要强转
	const TArray<FName> RowNames = KeyMappingDT->GetRowNames();
	for (const FName& RowName : RowNames)
	{
		FKeyInfoHeader* KeyInfoHeader = KeyMappingDT->FindRow<FKeyInfoHeader>(RowName, TEXT("KeySettingsContext"));
		if (!KeyInfoHeader)
		{
			continue;
		}

		UKeyInfoWidget* KeyInfoWidget = CreateWidget<UKeyInfoWidget>(GetOwningPlayer(), WidgetClass);
		if (!KeyInfoWidget)
		{
			continue;
		}

		// 获取用户自定义按键，优先使用存档中的按键，没有则用默认
		FKey Key = GetCustomKey(RowName);
		if (!Key.IsValid())
		{
			Key = KeyInfoHeader->DefaultKey;
		}

		KeyInfoWidget->InitPanel(RowName, KeyInfoHeader->KeyDescribe, Key);
		KeyMappingScrollBox->AddChild(KeyInfoWidget);
	}
}

FKey UKeySettingsWidget::GetCustomKey(FName KeyEventName)
{
	FKey Key;

	if (!UGameplayStatics::DoesSaveGameExist(ZeldaGameSlots::CustomUserKey, 0))
	{
		return Key;
	}

	if (!CustomKeyMapping)
	{
		CustomKeyMapping = Cast<UCustomKeyMapping>(UGameplayStatics::LoadGameFromSlot(ZeldaGameSlots::CustomUserKey, 0));
	}

	if (CustomKeyMapping && CustomKeyMapping->KeyMap.Contains(KeyEventName))
	{
		Key = CustomKeyMapping->KeyMap[KeyEventName];
	}

	return Key;
}

void UKeySettingsWidget::ResetAllKeys()
{
	if (!CustomKeyMapping)
	{
		return;
	}

	// UObject 指针不能直接 delete，置空后 GC 会回收
	CustomKeyMapping = nullptr;
	UGameplayStatics::DeleteGameInSlot(ZeldaGameSlots::CustomUserKey, 0);

	if (!KeyMappingDT || !KeyMappingScrollBox)
	{
		return;
	}

	for (int32 i = 0; i < KeyMappingScrollBox->GetChildrenCount(); ++i)
	{
		UKeyInfoWidget* KeyInfoWidget = Cast<UKeyInfoWidget>(KeyMappingScrollBox->GetChildAt(i));
		if (!KeyInfoWidget)
		{
			continue;
		}

		FKeyInfoHeader* KeyInfoHeader = KeyMappingDT->FindRow<FKeyInfoHeader>(KeyInfoWidget->GetKeyEventName(), TEXT("ResetKeysContext"));
		if (KeyInfoHeader)
		{
			KeyInfoWidget->ForceChangeKey(KeyInfoHeader->DefaultKey);
		}
	}
}

void UKeySettingsWidget::SaveCustomKey(FName KeyEventName, FKey NewKey)
{
	if (!CustomKeyMapping)
	{
		CustomKeyMapping = Cast<UCustomKeyMapping>(UGameplayStatics::CreateSaveGameObject(UCustomKeyMapping::StaticClass()));
	}

	if (CustomKeyMapping->KeyMap.Contains(KeyEventName))
	{
		CustomKeyMapping->KeyMap[KeyEventName] = NewKey;
	}
	else
	{
		CustomKeyMapping->KeyMap.Add(KeyEventName, NewKey);
	}

	UGameplayStatics::SaveGameToSlot(CustomKeyMapping, ZeldaGameSlots::CustomUserKey, 0);
}
