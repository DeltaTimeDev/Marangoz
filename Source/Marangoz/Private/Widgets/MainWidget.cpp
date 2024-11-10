// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/MainWidget.h"

#include "Components/TextBlock.h"

void UMainWidget::SetMoney(int32 NewMoney)
{
	MoneyText->SetText(FText::AsCurrency(NewMoney));
}
