// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/OrderTable.h"

#include "Data/ProjectDataSettings.h"
#include "Gameplay/OrderActor.h"
#include "Gameplay/ProductActor.h"


// Sets default values
AOrderTable::AOrderTable()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	RootComponent = MeshComponent;


}

// Called when the game starts or when spawned
void AOrderTable::BeginPlay()
{
	Super::BeginPlay();

	if (HasAuthority())
	{
		for (FName SpawnPoint : SpawnPointSocketNames)
		{
			SpawnOrderActor(SpawnPoint);
		}
		GetWorld()->GetTimerManager().SetTimer(OrderTimer, this, &AOrderTable::OnOrderTimerTicks, 3,true);
	
	}


	if (const UProjectDataSettings* ProductSettings = GetDefault<UProjectDataSettings>())
	{
		ProductDataAsset = ProductSettings->Products.LoadSynchronous();
	}
}

// Called every frame
void AOrderTable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AOrderTable::SpawnOrderActor(FName SocketName)
{
	if (MeshComponent->DoesSocketExist(SocketName))
	{
		const FTransform SpawnTransform = MeshComponent->GetSocketTransform(SocketName);
		
		if (AOrderActor* OrderActor = GetWorld()->SpawnActorDeferred<AOrderActor>(OrderActorsClass,SpawnTransform))
		{
			FOrder Order;
			Order.IsActive = false;
			OrderActor->SetOrder(Order);
			OrderActor->FinishSpawning(SpawnTransform);
			OrderActors.Add(OrderActor);
		}
	}
}

void AOrderTable::OnOrderTimerTicks()
{
	FOrder Order;
	Order.Name = "Dagger";
	Order.Color = FLinearColor::Green;

	if (ProductDataAsset)
	{
		FProductData Data;
		const int32 RandomProductIndex = FMath::RandRange(0, ProductDataAsset->Products.Num()-1);
		if (ProductDataAsset->Products.IsValidIndex(RandomProductIndex))
		{
			Data = ProductDataAsset->Products[RandomProductIndex];
		}
		 
		Order.Name = Data.Name;
		Order.ID = Data.ID;
		Order.Color = GetRandomColor();
	}
	
	for (AOrderActor* OrderActor : OrderActors)
	{
		if (!OrderActor->Order.IsActive)
		{
			Order.IsActive = true;
			OrderActor->SetOrder(Order);
			return;
		}
	}
}

FLinearColor AOrderTable::GetRandomColor()
{
	int32 RandomIndex = FMath::RandRange(0, Colors.Num() - 1);
	return Colors[RandomIndex];
}

