// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "ZeldaGame/Character/ZeCharacterBase.h"
#include "ZeAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class ZELDAGAME_API UZeAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	protected:
	virtual void NativeUpdateAnimation(float DeltaSeconds)override;



protected:
	UPROPERTY(BlueprintReadOnly)
	float Speed;
	
	UPROPERTY(BlueprintReadOnly)
	float Direction;
	
	UPROPERTY(BlueprintReadOnly)
	bool bIsCrouching;
	UPROPERTY()
	TObjectPtr<AZeCharacterBase>OwnerCharacter;
	UPROPERTY(BlueprintReadOnly)
	bool bSprinting;

};
