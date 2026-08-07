// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ZeCharacterBase.generated.h"

UCLASS()
class ZELDAGAME_API AZeCharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AZeCharacterBase(const FObjectInitializer& ObjectInitializer=FObjectInitializer::Get());

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	void DoCrouch();

	void StartSprint();
	void StopSprint();

	bool bSprinting;
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	bool IsSprinting() const{return bSprinting;};

	
};
