// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ProductCatalogWidget.generated.h"

class UProduct;
/**
 * 
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCreateCommandDelegate, UProduct*, SelectedProduct);

UCLASS()
class MARANGOZ_API UProductCatalogWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintAssignable, Category="Events")
	FOnCreateCommandDelegate OnRequestForChangeSelection;

	UPROPERTY(BlueprintAssignable, Category="Events")
	FOnCreateCommandDelegate OnCreateCommand;

	UFUNCTION(BlueprintCallable, Category="Catalog")
	void AddProduct(UProduct* Product);

	UFUNCTION(BlueprintCallable, Category="Catalog")
	void OnButtonClicked();

	UFUNCTION()
	void SelectProduct(UProduct* InSelectedProduct);

	UFUNCTION()
	void SelectProductByID(FGuid ProductID);
	


protected:
	virtual void NativeConstruct() override;
	
	UPROPERTY(meta = (BindWidget))
	class UListView* ProductList;

	UPROPERTY(meta = (BindWidget))
	class UButton* ActionButton; 

	UPROPERTY()
	UProduct* CurrentSelectedProduct;

	UFUNCTION()
	void OnProductSelected(UObject* Item);

	UFUNCTION()
	void SetProductWidgetsSelected(UProduct* InSelectedProduct);

	UFUNCTION()
	void SetProductWidgetsSelectedByID(FGuid SelectedProductID);

	
};
