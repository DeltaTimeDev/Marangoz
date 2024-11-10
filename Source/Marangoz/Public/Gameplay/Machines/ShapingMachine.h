// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Gameplay/ProductActor.h"
#include "MachineBase.h"
#include "ShapingMachine.generated.h"


UCLASS()
class MARANGOZ_API AShapingMachine : public AMachineBase
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AShapingMachine();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

public:
	UFUNCTION(BlueprintCallable, Category="Product")
	void SpawnProduct();

	UFUNCTION()
	void OnRequestForChangeSelection(UProduct* SelectedProduct);

	UFUNCTION()
	void OnCreateProductCommand(UProduct* CreateProduct);

	UFUNCTION()
	void OnSelectedProductIdChanged(FGuid NewCurrentSelectedProductId);

	UFUNCTION()
	void SetSelectedProductOnServer(FGuid SelectedProductID);

	UPROPERTY(EditAnywhere)
	TSubclassOf<class AProductActor> ProductClass;

private:

	 UPROPERTY(EditAnywhere, Category="Components")
	 UStaticMeshComponent* WidgetHolderMeshComponent;
	
	// UPROPERTY(VisibleAnywhere, Category="Components")
	// UStaticMeshComponent* KeyboardMeshComponent;
	
	UPROPERTY(VisibleAnywhere, Category="Components")
	class UWidgetComponent* ProductCatalogWidgetComponent;

	



	UPROPERTY(EditAnywhere, Category="UI")
	TSubclassOf<class UProductCatalogWidget> ProductCatalogWidgetClass;

	FName SpawnSocketName = TEXT("SpawnSocket"); 

	UPROPERTY()
	UProductCatalogWidget* ProductCatalogWidgetInstance;

	UPROPERTY(EditAnywhere)
	UProductDataAsset* ProductDataAsset;
	
	//UPROPERTY(VisibleAnywhere)
	//UProduct* CurrentSelectedProduct;

	FProductData* GetProductByID(FGuid ProductID);

	UPROPERTY(ReplicatedUsing= OnSelectedProductIdChanged, VisibleAnywhere)
	FGuid CurrentSelectedProductID;

	UPROPERTY()
	class AMarangozPlayerController* MarangozPlayerController;
};
