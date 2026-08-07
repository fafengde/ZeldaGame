// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "ZeldaGame/UMG/MainMenu/KeySettingsWidget.h"
#include "ZeldaGame/Data/KeyMapping/CustomKeyMapping.h"
#include "ZeldaGame/ZeldaGame.h"
#include "InputMappingContext.h"
#include "Kismet/GameplayStatics.h"
#include "InputCoreTypes.h"
#include "GameFramework/GameUserSettings.h"
#include "ZeldaGame/Settings/ZeUserSettings.h"

#define INSERT_ACTION(ActionName)if (KeyMappingDT->GetRowMap().Contains(TEXT(ActionName)))\
		{\
			FKeyInfoHeader*KeyInfoHeader=reinterpret_cast<FKeyInfoHeader*>(KeyMappingDT->GetRowMap()[TEXT(ActionName)]);\
			\
			FKey Key=GetCustomKey(TEXT(ActionName));\
			if (!Key.IsValid())\
			{\
				Key=KeyInfoHeader->DefaultKey;\
			}\
			IMC_Player->MapKey(KeyInfoHeader->InputAction,Key);\
		}

// Sets default values
APlayerCharacter::APlayerCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SpringArmComponent=CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	SpringArmComponent->SetupAttachment(RootComponent);
	SpringArmComponent->bUsePawnControlRotation=true;
	CameraComponent=CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComponent->SetupAttachment(SpringArmComponent);

	
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	SetupPlayerInputMappingContext();
	
}

void APlayerCharacter::SetupPlayerInputMappingContext()
{
	//装载映射表
	if (APlayerController*Pc=Cast<APlayerController>(GetController()))
	{
		//通过读取表格，从表格中读取数据，写入到我们的输入映射表格文件中
		if (!KeyMappingDT)
		{
			KeyMappingDT=LoadObject<UDataTable>(this,TEXT("/Script/Engine.DataTable'/Game/ZeldaGame/Data/DT_KeyMapping.DT_KeyMapping'"));
		}
		ensure(KeyMappingDT);//错误断言

		if (!IMC_Player)
		{
			IMC_Player=LoadObject<UInputMappingContext>(this,TEXT("/Script/EnhancedInput.InputMappingContext'/Game/ZeldaGame/Enhanced/IMC_Player.IMC_Player'"));
		}
		

		//清理旧的映射关系
		IMC_Player->UnmapAll();
		
		//读取表格数据
		INSERT_ACTION("Jump");
		INSERT_ACTION("Crouch");
		INSERT_ACTION("Look");
		INSERT_ACTION("Sprint");
		
		InsertAxisAction(TEXT("MoveForward"),EAxis::Y,false);
		InsertAxisAction(TEXT("MoveBack"),EAxis::Y,true);
		InsertAxisAction(TEXT("MoveLeft"),EAxis::X,true);
		InsertAxisAction(TEXT("MoveRight"),EAxis::X,false);
		//获取增强输入的子系统
		UEnhancedInputLocalPlayerSubsystem* Subsystem=ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(Pc->GetLocalPlayer());
		//装载映射表
		Subsystem->AddMappingContext(IMC_Player,0);
	}
}

FKey APlayerCharacter::GetCustomKey(FName KeyEventName)
{
	//从存档文件中，读取数据
	if (!CustomKeyMapping&&!UGameplayStatics::DoesSaveGameExist(CUSTOM_USER_KEY_SLOT,0))
	{
		return FKey() ;
	}
	if (!CustomKeyMapping)
	{
		//读档
		CustomKeyMapping=Cast<UCustomKeyMapping>(UGameplayStatics::LoadGameFromSlot(CUSTOM_USER_KEY_SLOT,0));
	}
	if (CustomKeyMapping->KeyMap.Contains(KeyEventName))
	{
		return CustomKeyMapping->KeyMap[KeyEventName];
	}
	return FKey() ;
}

UInputAction* APlayerCharacter::GetInputAction(FName RomName)
{
	if (!KeyMappingDT)
	{
		KeyMappingDT=LoadObject<UDataTable>(this,TEXT("/Script/Engine.DataTable'/Game/ZeldaGame/Data/DT_KeyMapping.DT_KeyMapping'"));
	}
	if (KeyMappingDT->GetRowMap().Contains(RomName))
	{
		FKeyInfoHeader*KeyInfoHeader=reinterpret_cast<FKeyInfoHeader*>(KeyMappingDT->GetRowMap()[RomName]);
		return KeyInfoHeader->InputAction;
	}
	return nullptr;
}

void APlayerCharacter::Move(const FInputActionValue& InputValue)
{
	//获取输入的轴值
	FVector2D InputAValue2D=InputValue.Get<FVector2D>();	//角色移动
	/*AddMovementInput(GetActorForwardVector(),InputAValue2D.Y);//前后
	AddMovementInput(GetActorRightVector(),InputAValue2D.X);//左右*/
	FRotator NewRotation(0,GetControlRotation().Yaw,0);
	FQuat Quat =NewRotation.Quaternion();
	AddMovementInput(Quat.GetAxisX(),InputAValue2D.Y);//前后
	AddMovementInput(Quat.GetAxisY(),InputAValue2D.X);//左右
}

void APlayerCharacter::InsertAxisAction(FName ActionName, EAxis::Type AxisType, bool bNagate)
{
	if (KeyMappingDT->GetRowMap().Contains(ActionName))
	{
		FKeyInfoHeader*KeyInfoHeader=reinterpret_cast<FKeyInfoHeader*>(KeyMappingDT->GetRowMap()[ActionName]);
		//检查是否存储过自定义按键
		FKey Key=GetCustomKey(ActionName);
		if (!Key.IsValid())
		{
			Key=KeyInfoHeader->DefaultKey;
		}
		FEnhancedActionKeyMapping&KeyMapping=IMC_Player->MapKey(KeyInfoHeader->InputAction,Key);
		//修正器
		if (bNagate)
		{
			KeyMapping.Modifiers.Add(NewObject<UInputModifierNegate>(IMC_Player));
		}
		if (AxisType == EAxis::Y)
		{
			KeyMapping.Modifiers.Add(NewObject<UInputModifierSwizzleAxis>(IMC_Player));
		}
	}
}

void APlayerCharacter::Look(const FInputActionValue& InputValue)
{
	FVector2D InputAValue2D=InputValue.Get<FVector2D>();

	if (MouseSpeed==0)
	{
	//读取配置文件
		if (UZeUserSettings* GameUserSettings = Cast<UZeUserSettings>(UGameUserSettings::GetGameUserSettings()))
		{
			MouseSpeed=GameUserSettings->GetMouseSpeed();
		}
		else
		{
			MouseSpeed=30;
		}
	}
	AddControllerPitchInput(-InputAValue2D.Y*GetWorld()->GetDeltaSeconds()*30);
	AddControllerYawInput(InputAValue2D.X*GetWorld()->GetDeltaSeconds()*30);
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	//绑定Action的逻辑
	if (UEnhancedInputComponent* EnhancedInputComponent=Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		//绑定
		if (UInputAction*InputAction=GetInputAction(TEXT("Jump")))
		{
			EnhancedInputComponent->BindAction(InputAction,ETriggerEvent::Completed,this,&ThisClass::Jump);
		}
		if (UInputAction*InputAction=GetInputAction(TEXT("Crouch")))
		{
			EnhancedInputComponent->BindAction(InputAction,ETriggerEvent::Completed,this,&ThisClass::DoCrouch);
		}
		if (UInputAction*InputAction=GetInputAction(TEXT("MoveForward")))
		{
			EnhancedInputComponent->BindAction(InputAction,ETriggerEvent::Triggered,this,&ThisClass::Move);
		}
		if (UInputAction*InputAction=GetInputAction(TEXT("Look")))
		{
			EnhancedInputComponent->BindAction(InputAction,ETriggerEvent::Triggered,this,&ThisClass::Look);
		}
		if (UInputAction*InputAction=GetInputAction(TEXT("Sprint")))
		{
			EnhancedInputComponent->BindAction(InputAction,ETriggerEvent::Started,this,&ThisClass::StartSprint);
			EnhancedInputComponent->BindAction(InputAction,ETriggerEvent::Completed,this,&ThisClass::StopSprint);
		}
	}
}
#undef INSERT_ACTION
