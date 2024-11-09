// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "Blueprint/UserWidget.h"
#include "ProductWidget.generated.h"

/**
 * 
 */



UCLASS()
class MARANGOZ_API UProductWidget : public UUserWidget,public IUserObjectListEntry
{
	GENERATED_BODY()

public:
	virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;
	

protected:
	UPROPERTY(meta = (BindWidget))
	class UImage* ProductImage;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* ProductName;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* ProductPrice;
	
	UPROPERTY(meta = (BindWidget))
	class UBorder* SelectionBorder;

public:
	void SetSelected(bool bIsSelected);

	UPROPERTY(EditAnywhere)
	FLinearColor SelectedColor = FLinearColor::Yellow;

	UPROPERTY(EditAnywhere)
	FLinearColor UnselectedColor =  FLinearColor::Transparent;
};
