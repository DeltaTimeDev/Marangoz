// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/PaintCan.h"

void UPaintCan::SetColor(FLinearColor NewColor)
{	
	UMaterialInstanceDynamic* DynamicMaterial = CreateAndSetMaterialInstanceDynamic(0);
	if (DynamicMaterial)
	{
		DynamicMaterial->SetVectorParameterValue("PaintColor", NewColor);
	}
	Color = NewColor;
}

void UPaintCan::SelectCan()
{
	UE_LOG(LogTemp, Warning, TEXT("Select Can"));
	OnPaintCanSelected.Broadcast(this);
}
