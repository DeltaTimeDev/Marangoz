// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/ProductCatalogWidget.h"

#include "Components/Border.h"
#include "Components/Button.h"
#include "Components/ListView.h"
#include "Gameplay/ShapingMachine.h"
#include "Widgets/ProductWidget.h"

void UProductCatalogWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if(ProductList)
	{
		ProductList->OnItemSelectionChanged().AddUObject(this, &UProductCatalogWidget::OnProductSelected);
	}

	if(ActionButton)
	{
		//ActionButton->OnClicked.
		ActionButton->OnPressed.AddDynamic(this, &UProductCatalogWidget::OnButtonClicked);
	}
}

void UProductCatalogWidget::SelectProduct(UProduct* InSelectedProduct)
{
	SetProductWidgetsSelected(InSelectedProduct);
}

void UProductCatalogWidget::SelectProductByID(FGuid ProductID)
{
	SetProductWidgetsSelectedByID(ProductID);
}

void UProductCatalogWidget::OnProductSelected(UObject* Item)
{
	if (UProduct* SelectedProduct = Cast<UProduct>(Item))
	{
		OnRequestForChangeSelection.Broadcast(SelectedProduct);
	}
	
	// SelectedProduct = Cast<UProduct>(Item);
	// SetProductWidgetsSelected(SelectedProduct);
	// OnSelectionChanged.Broadcast(SelectedProduct);
}

void UProductCatalogWidget::SetProductWidgetsSelected(UProduct* InSelectedProduct)
{
	CurrentSelectedProduct = InSelectedProduct;
	for(UObject* ListItem : ProductList->GetListItems())
	{
		UProductWidget* ProductWidget = Cast<UProductWidget>(ProductList->GetEntryWidgetFromItem(ListItem));
		if(ProductWidget)
		{
			ProductWidget->SetSelected(ListItem == InSelectedProduct);
		}
	}
}

void UProductCatalogWidget::SetProductWidgetsSelectedByID(FGuid SelectedProductID)
{
	for(UObject* ListItem : ProductList->GetListItems())
	{
		if (UProduct* Product = Cast<UProduct>(ListItem))
		{
			if (UProductWidget* ProductWidget = Cast<UProductWidget>(ProductList->GetEntryWidgetFromItem(ListItem)))
			{
				if (Product->Data.ID == SelectedProductID)
				{
					ProductWidget->SetSelected(true);
					CurrentSelectedProduct = Product;
				}
				else
				{
					ProductWidget->SetSelected(false);
				}
			}
		}
	}
}

void UProductCatalogWidget::AddProduct(UProduct* Product)
{
	if(ProductList && Product)
	{
		ProductList->AddItem(Product);
	}
}

void UProductCatalogWidget::OnButtonClicked()
{
	if(CurrentSelectedProduct)
	{
		UE_LOG(LogTemp, Log, TEXT("Selected Product: %s"), *CurrentSelectedProduct->Data.Name);
		OnCreateCommand.Broadcast(CurrentSelectedProduct);
	}
}



