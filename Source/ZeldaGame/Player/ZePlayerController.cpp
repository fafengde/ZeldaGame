// Fill out your copyright notice in the Description page of Project Settings.


#include "ZePlayerController.h"

#include "ZeldaGame/Manager/ZePlayerCameraManager.h"

AZePlayerController::AZePlayerController()
{
	PlayerCameraManagerClass=AZePlayerCameraManager::StaticClass();
}
