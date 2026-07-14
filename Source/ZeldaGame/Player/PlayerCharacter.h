// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ZeldaGame/Character/ZeCharacterBase.h"
#include "PlayerCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;

UCLASS()
class ZELDAGAME_API APlayerCharacter : public AZeCharacterBase
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	protected:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USpringArmComponent>SpringArmComponent;
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UCameraComponent>CameraComponent;
};
