// Fill out your copyright notice in the Description page of Project Settings.


#include "ZeAnimInstance.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

void UZeAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	//更新状态数据

	if (!OwnerCharacter)
	{
		OwnerCharacter=Cast<AZeCharacterBase>(TryGetPawnOwner());
		return;
	}

	//获取角色速度
	Speed=OwnerCharacter->GetVelocity().Size2D();
	bSprinting=OwnerCharacter->IsSprinting()&&Speed>0.0f;

	
	bIsCrouching = OwnerCharacter->GetCharacterMovement()->IsCrouching();

	
	if (Speed > 10.0f)
	{
		const FRotator ActorRot    = OwnerCharacter->GetActorRotation();
		const FRotator VelocityRot = OwnerCharacter->GetVelocity().ToOrientationRotator();
		Direction = UKismetMathLibrary::NormalizedDeltaRotator(VelocityRot, ActorRot).Yaw;
	}

}
