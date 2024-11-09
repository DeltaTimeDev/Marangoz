// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "PaintCan.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSelectPaintCanDelegate, FLinearColor, Color);


/**
 * 
 */
UCLASS()
class MARANGOZ_API UPaintCan : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
	void SetColor(FLinearColor NewColor);

	void SelectCan();

	FLinearColor Color;

	FSelectPaintCanDelegate OnPaintCanSelected;

};
