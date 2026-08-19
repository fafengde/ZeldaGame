// Fill out your copyright notice in the Description page of Project Settings.


#include "ZePlayerCameraManager.h"

#include "ZeldaGame/Player/PlayerCharacter.h"

void AZePlayerCameraManager::UpdateCamera(float DeltaTime)
{
	//蹲下时修改吊臂的Z轴位置是站立时候的高度，然后慢慢向蹲下去的Z轴高度相等
	if (APlayerCharacter*Player=Cast<APlayerCharacter>(GetOwningPlayerController()->GetPawn()))
	{
		Player->GetSpringArmComponent();
	}

	//先修改相机位置，再执行父类函数
	Super::UpdateCamera(DeltaTime);

	
}
