// Fill out your copyright notice in the Description page of Project Settings.


#include "ZeGameMode.h"

#include "ZeldaGame/Player/PlayerCharacter.h"

AZeGameMode::AZeGameMode()
{
	//配置角色蓝图类
	//通过FClassFinder查找蓝图路径并设置为默认Pawn
	ConstructorHelpers::FClassFinder<APlayerCharacter> PlayerClass(TEXT("/Script/Engine.Blueprint'/Game/ZeldaGame/Player/BP_Player.BP_Player_C'"));
	DefaultPawnClass = PlayerClass.Class;
}
