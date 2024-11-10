// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/Machines/ShapingMachine.h"

#include "Components/WidgetComponent.h"
#include "Framework/MarangozPlayerController.h"
#include "Gameplay/ProductActor.h"
#include "Gameplay/Subsystem/MoneySubsystem.h"
#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"
#include "Widgets/ProductCatalogWidget.h"
#include "Gameplay/Subsystem/MoneySubsystem.h"

// Sets default values
AShapingMachine::AShapingMachine()
{
	PrimaryActorTick.bCanEverTick = false;
	

	WidgetHolderMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WidgetHolderMeshComponent"));
	WidgetHolderMeshComponent->SetupAttachment(RootComponent);

	ProductCatalogWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("ProductCatalogWidgetComponent"));
	ProductCatalogWidgetComponent->SetupAttachment(WidgetHolderMeshComponent);

	

	// if (ProductCatalogWidgetClass)
	// {
	// 	ProductCatalogWidgetComponent->SetWidgetClass(ProductCatalogWidgetClass);
	// }
	//ProductCatalogWidgetComponent->SetWidgetSpace(EWidgetSpace::Screen);
}

// Called when the game starts or when spawned
void AShapingMachine::BeginPlay()
{
	Super::BeginPlay();

	if (APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0))
	{
		MarangozPlayerController = Cast<AMarangozPlayerController>(PlayerController);
	}
	
	
	ProductCatalogWidgetInstance = Cast<UProductCatalogWidget>(ProductCatalogWidgetComponent->GetUserWidgetObject());
	if (ProductCatalogWidgetInstance)
	{
		ProductCatalogWidgetInstance->OnRequestForChangeSelection.AddDynamic(this, &AShapingMachine::OnRequestForChangeSelection);
		ProductCatalogWidgetInstance->OnCreateCommand.AddDynamic(this, &AShapingMachine::OnCreateProductCommand);

		if (IsValid(ProductDataAsset))
		{
			for (FProductData ProductData : ProductDataAsset->Products)
			{
				UProduct* NewProductObject = NewObject<UProduct>(this);
				NewProductObject->Data = ProductData;
				ProductCatalogWidgetInstance->AddProduct(NewProductObject);
			}
		}
	}
}

void AShapingMachine::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AShapingMachine, CurrentSelectedProductID);
}

void AShapingMachine::SpawnProduct()
{
	FProductData* CurrentSelectedProductData = GetProductByID(CurrentSelectedProductID);
	
	
	if (CurrentSelectedProductData && MachineMeshComponent->DoesSocketExist(SpawnSocketName))
	{
		const FTransform SpawnTransform = MachineMeshComponent->GetSocketTransform(SpawnSocketName);

		// if (AProductActor* ProductActor = GetWorld()->SpawnActorDeferred<AProductActor>(ProductClass,SpawnTransform))
		// {
		// 	ProductActor->SetProductData(*CurrentSelectedProductData);
		// 	ProductActor->FinishSpawning(SpawnTransform);
		// }
		if (AProductActor* ProductActor = GetWorld()->SpawnActor<AProductActor>(ProductClass,SpawnTransform))
		{
			ProductActor->SetProductData(*CurrentSelectedProductData);

			if (UMoneySubsystem* MoneySubsystem = Cast<UMoneySubsystem>(GetGameInstance()->GetSubsystem<UMoneySubsystem>()))
			{
				MoneySubsystem->Spend(CurrentSelectedProductData->RawMaterialCost);
			}
			
			//ProductActor->FinishSpawning(SpawnTransform);
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No product selected or socket not found."));
	}
}

void AShapingMachine::OnRequestForChangeSelection(UProduct* SelectedProduct)
{
	if (HasAuthority())
	{
		SetSelectedProductOnServer(SelectedProduct->Data.ID);
	}
	else
	{
		if (IsValid(MarangozPlayerController))
		{
			MarangozPlayerController->ServerSetProductShapingMachine(this, SelectedProduct->Data.ID);
		}
	}
}

void AShapingMachine::OnSelectedProductIdChanged(FGuid NewCurrentSelectedProductId)
{
	ProductCatalogWidgetInstance->SelectProductByID(CurrentSelectedProductID);
}

void AShapingMachine::SetSelectedProductOnServer(FGuid SelectedProductID)
{
	CurrentSelectedProductID = SelectedProductID;
	OnSelectedProductIdChanged(SelectedProductID);
}

FProductData* AShapingMachine::GetProductByID(FGuid ProductID)
{
	FProductData* TargetData = ProductDataAsset->Products.FindByPredicate([ProductID](FProductData Data)
	{
		return ProductID == Data.ID; 
	});
	
	return TargetData;
}

void AShapingMachine::OnCreateProductCommand(UProduct* CreateProduct)
{
	if (HasAuthority())
	{
		SpawnProduct();
	}
	else
	{
		if (IsValid(MarangozPlayerController))
		{
			MarangozPlayerController->ServerSpawnProduct(this);
		}
	}
	
}
