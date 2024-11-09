// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/ProductWidget.h"

#include "Components/Border.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Gameplay/ShapingMachine.h"

void UProductWidget::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	UProduct* Product = Cast<UProduct>(ListItemObject);
	if(Product)
	{
		ProductName->SetText(FText::FromString(Product->Data.Name));
		ProductPrice->SetText(FText::AsCurrency(Product->Data.Price));
		ProductImage->SetBrushFromTexture(Product->Data.Image);
	}
	SetSelected(false);
}

void UProductWidget::SetSelected(bool bIsSelected)
{
	const FLinearColor BorderColor = bIsSelected ? SelectedColor : UnselectedColor;
	SelectionBorder->SetBrushColor(BorderColor);
}
