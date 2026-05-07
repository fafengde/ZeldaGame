// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "CustomKeyMapping.generated.h"

/**
 * 
 */
UCLASS()
class ZELDAGAME_API UCustomKeyMapping : public USaveGame
{
	GENERATED_BODY()
	public:
	//数据容器
	UPROPERTY()
	TMap<FName ,FKey> KeyMap;
};
