// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ZeldaGame/Character/ZeCharacterBase.h"
#include "PlayerCharacter.generated.h"

struct FInputActionValue;
class UCustomKeyMapping;
class UInputAction;
class UCameraComponent;
class USpringArmComponent;
class UInputMappingContext;

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

	void SetupPlayerInputMappingContext();
	FKey GetCustomKey(FName KeyEventName);
	UInputAction* GetInputAction(FName RomName);
	void Move(const FInputActionValue& InputValue);
	void InsertAxisAction(FName ActionName,EAxis::Type AxisType,bool bNagate );
	void Look(const FInputActionValue& InputValue);
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	TObjectPtr<USpringArmComponent>GetSpringArmComponent()const {return SpringArmComponent;}
	TObjectPtr<UCameraComponent> GetCameraComponent()const {return CameraComponent;}
	
	protected:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USpringArmComponent>SpringArmComponent;
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UCameraComponent>CameraComponent;
	
	UPROPERTY(EditAnywhere)
	TObjectPtr<UInputMappingContext>IMC_Player;

	UPROPERTY()
	TObjectPtr<UDataTable>KeyMappingDT;
	UPROPERTY()
	TObjectPtr<UCustomKeyMapping>CustomKeyMapping;

	UPROPERTY()
	float MouseSpeed;
	
};
