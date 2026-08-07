// Fill out your copyright notice in the Description page of Project Settings.


#include "ZeCharacterBase.h"

#include "ZeldaGame/Compents/ZeCharacterMovementCompent.h"


// Sets default values
AZeCharacterBase::AZeCharacterBase(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer.SetDefaultSubobjectClass<UZeCharacterMovementCompent>(CharacterMovementComponentName))
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bUseControllerRotationYaw = false;
}

// Called when the game starts or when spawned
void AZeCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void AZeCharacterBase::DoCrouch()
{
	//执行蹲伏逻辑
	if (CanCrouch())
	{
		Crouch();
	}
	else
	{
		UnCrouch();
	}
}

void AZeCharacterBase::StartSprint()
{
	bSprinting=true;
}

void AZeCharacterBase::StopSprint()
{
	bSprinting=false;
}

// Called every frame
void AZeCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AZeCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

