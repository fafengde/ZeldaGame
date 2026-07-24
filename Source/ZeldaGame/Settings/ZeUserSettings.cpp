// Fill out your copyright notice in the Description page of Project Settings.


#include "ZeUserSettings.h"

UZeUserSettings::UZeUserSettings()
{
	MouseSpeedScale=0.5f;
}

float UZeUserSettings::GetMouseSpeed() const
{
	return 15+30*MouseSpeedScale;
}
