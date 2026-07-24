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
	KeyMappingDT=LoadObject<UDataTable>(this,TEXT("/Script/Engine.DataTable'/Game/ZeldaGame/Data/DT_KeyMapping.DT_KeyMapping'"));
	if (KeyMappingDT)
	{
		TSubclassOf<UKeyInfoWidget>WidgetClass =LoadClass<UKeyInfoWidget>(nullptr,TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/ZeldaGame/UMG/MainMenu/WBP_KeyInfo.WBP_KeyInfo_C'")) ;
		for (auto Kv: KeyMappingDT->GetRowMap())
		{
			// Kv.Key;
			// Kv.Value;
			FKeyInfoHeader*KeyInfoHeader=reinterpret_cast<FKeyInfoHeader*>(Kv.Value);
			if (KeyInfoHeader->KeyDescribe.IsEmpty())
			{
				continue;
			}
			UKeyInfoWidget*KeyInfoWidget=CreateWidget<UKeyInfoWidget>(GetOwningPlayer(),WidgetClass);
			if (KeyInfoWidget)
			{
				//获取用户自定义按键，如果有，则用自定义的，没有则用默认的
				FKey Key = GetCustomKey(Kv.Key);
				//检查Key的值是否有效，如果有效，则表明有存档，如果无效，则表明没有存档
				if (!Key.IsValid())
				{
					Key = KeyInfoHeader->DefaultKey;
				}
				KeyInfoWidget->InitPanel(Kv.Key,KeyInfoHeader->KeyDescribe,Key);
				KeyMappingScrollBox->AddChild(KeyInfoWidget);
			}
		}
	}
}

FKey UKeySettingsWidget::GetCustomKey(FName KeyEventName)
{
	//获取用户存档数据
	FKey Key;
	//检查是否存在存档
	if (UGameplayStatics::DoesSaveGameExist(CUSTOM_USER_KEY_SLOT,0))
	{

		if (!CustomKeyMapping)
		{
			//第一次打开则读取存档
			CustomKeyMapping=Cast<UCustomKeyMapping>(UGameplayStatics::LoadGameFromSlot(CUSTOM_USER_KEY_SLOT,0));
		}
		// // 每次都重新加载，确保数据最新
		// UCustomKeyMapping* TempMapping = Cast<UCustomKeyMapping>(UGameplayStatics::LoadGameFromSlot(CUSTOM_USER_KEY_SLOT, 0));

		if (CustomKeyMapping->KeyMap.Contains(KeyEventName))//如果存过则直接使用存储的按键
		{
			Key = CustomKeyMapping->KeyMap[KeyEventName];
		}
		return Key;
	}



	return Key;
}

void UKeySettingsWidget::ResetAllKeys()
{
	//重置所有按键
	//删掉之前的按键存档
	if (CustomKeyMapping)
	{
		CustomKeyMapping=nullptr;//注意，删除U类的指针不能直接Delete，直接为空，编辑器会直接回收的
		//删除本地存档
		UGameplayStatics::DeleteGameInSlot(CUSTOM_USER_KEY_SLOT,0);
		//还原UI
		if (KeyMappingDT)
		{
			for (int32 i=0;i<KeyMappingScrollBox->GetChildrenCount();++i)
			{
				if (UKeyInfoWidget*KeyInfoWidget=Cast<UKeyInfoWidget>(KeyMappingScrollBox->GetChildAt(i)))
				{
					if (KeyMappingDT->GetRowMap().Contains(KeyInfoWidget->GetKeyEventName()))
					{
						FKeyInfoHeader*KeyInfoHeader=reinterpret_cast<FKeyInfoHeader*>(KeyMappingDT->GetRowMap()[KeyInfoWidget->GetKeyEventName()]);
						KeyInfoWidget->ForceChangeKey(KeyInfoHeader->DefaultKey);
					}
				}
			}
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
