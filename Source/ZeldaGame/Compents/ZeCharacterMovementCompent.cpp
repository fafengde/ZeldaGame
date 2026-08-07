// Fill out your copyright notice in the Description page of Project Settings.


#include "ZeCharacterMovementCompent.h"

#include "ZeldaGame/Character/ZeCharacterBase.h"


// Sets default values for this component's properties
UZeCharacterMovementCompent::UZeCharacterMovementCompent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
	SprintSpeed=497.289f;
	MaxWalkSpeed=319.22f;
	
}


// Called when the game starts
void UZeCharacterMovementCompent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

float UZeCharacterMovementCompent::GetMaxSpeed() const
{
	float Speed=Super::GetMaxSpeed();
	//开始冲刺时的速度
	//获取使用组件的对象
	if (AZeCharacterBase*CharacterBase=Cast<AZeCharacterBase>(GetOwner()))
	{
		if (CharacterBase->IsSprinting())
		{
			Speed=SprintSpeed;
		}
	}
	
	return Speed;
}


// Called every frame
void UZeCharacterMovementCompent::TickComponent(float DeltaTime, ELevelTick TickType,
                                                FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

