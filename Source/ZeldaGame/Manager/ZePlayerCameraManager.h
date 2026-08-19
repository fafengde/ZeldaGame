// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/PlayerCameraManager.h"
#include "ZePlayerCameraManager.generated.h"

/**
 * 
 */
UCLASS()
class ZELDAGAME_API AZePlayerCameraManager : public APlayerCameraManager
{
	GENERATED_BODY()


protected:

	virtual void UpdateCamera(float DeltaTime) override;
};
