// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameUserSettings.h"
#include "ZeUserSettings.generated.h"

/**
 *
 */
UCLASS(config=GameUserSettings, BlueprintType)
class ZELDAGAME_API UZeUserSettings : public UGameUserSettings
{
	GENERATED_BODY()

public:
	UZeUserSettings();
	float GetMouseSpeed()const;

protected:
	UPROPERTY(BlueprintReadWrite,Config)
	float MouseSpeedScale;
};
