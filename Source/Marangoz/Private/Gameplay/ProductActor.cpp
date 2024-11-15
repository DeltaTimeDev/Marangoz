// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/ProductActor.h"

#include "Net/UnrealNetwork.h"

// Sets default values
AProductActor::AProductActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	RootComponent = MeshComponent;

	bReplicates = true;
}

void AProductActor::OnDataChanged(FProductData NewData)
{
	MeshComponent->SetStaticMesh(Data.Mesh);
	SetColor(Data.Color);
}

void AProductActor::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AProductActor, Data);
}

// Called when the game starts or when spawned
void AProductActor::BeginPlay()
{
	Super::BeginPlay();
	//SetProductData(Data);
}

// Called every frame
void AProductActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProductActor::SetProductData(FProductData InData)
{
	Data = InData;
	OnDataChanged(Data);
}

void AProductActor::SetColor(FLinearColor NewColor)
{
	UMaterialInstanceDynamic* DynamicMaterial = MeshComponent->CreateAndSetMaterialInstanceDynamic(0);
	if (DynamicMaterial)
	{
		DynamicMaterial->SetVectorParameterValue("WoodColor", NewColor);
	}
}

void AProductActor::Paint(FLinearColor NewColor)
{
	Data.Color = NewColor;
	OnDataChanged(Data);
}

