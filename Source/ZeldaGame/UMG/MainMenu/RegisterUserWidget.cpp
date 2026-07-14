// Fill out your copyright notice in the Description page of Project Settings.


#include "RegisterUserWidget.h"

#include "Components/Button.h"
#include "Components/EditableTextBox.h"
#include "Components/TextBlock.h"

void URegisterUserWidget::NativeConstruct()
{
	Super::NativeConstruct();
	SendCoudButton->OnClicked.AddDynamic(this,&ThisClass::OnSendCodeButtonClicked);
}

void URegisterUserWidget::OnSendCodeButtonClicked()
{
	//检查输入的文本是否符合邮箱格式
	FString InputMailString=MailTextBox->GetText().ToString();
	//构建Parttern表达式Regex
	FRegexPattern Pattern(TEXT("^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\\.[a-zA-Z]{2,}$"));
	FRegexMatcher Matcher(Pattern,InputMailString);//创建了一个匹配器
	//执行匹配器检查
	if (!Matcher.FindNext())
	{
		UE_LOG(LogTemp,Display,TEXT("输入邮箱格式错误，无法进行格式匹配"));
		return;
	}
	
	//将按钮变成不可用状态
	SendCoudButton->SetIsEnabled(false);
	//启动倒计时
	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle,this,&ThisClass::OnTimerCallback,1);
	SendButtonCooldownTick=SendCodeButtonTime;
	UpdateButtonText();//按钮触发的时候调用
}

void URegisterUserWidget::OnTimerCallback()
{
	--SendButtonCooldownTick;
	if(SendButtonCooldownTick>0)//说明冷却时间还没有结束
	{
		FTimerHandle TimerHandle;
		GetWorld()->GetTimerManager().SetTimer(TimerHandle,this,&ThisClass::OnTimerCallback,1);
	}
	else
	{
		SendCoudButton->SetIsEnabled(true);
	}
	UpdateButtonText();//计时的时候触发
}

void URegisterUserWidget::UpdateButtonText()
{
	if(SendButtonCooldownTick>0)
	{
		SendButtonTextBlock->SetText(FText::Format(NSLOCTEXT("ui","kvc945","发送({0})"),FText::AsNumber(SendButtonCooldownTick)));
	}
	else
	{
		SendButtonTextBlock->SetText(NSLOCTEXT("ui","dkc945","发送"));
	}
}

URegisterUserWidget::URegisterUserWidget(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)//显示调用父类参数构造
{
	SendCodeButtonTime=5  ;
}
