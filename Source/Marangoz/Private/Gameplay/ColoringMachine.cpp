// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/ColoringMachine.h"

#include "Components/BoxComponent.h"
#include "Framework/MarangozPlayerController.h"
#include "Gameplay/PaintCan.h"
#include "Gameplay/ProductActor.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AColoringMachine::AColoringMachine()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	RootComponent = MeshComponent;

	PaintingArea = CreateDefaultSubobject<UBoxComponent>(TEXT("PaintingArea"));
	PaintingArea->SetupAttachment(RootComponent);
	PaintingArea->SetHiddenInGame(false);

	RedPaintCan = CreateDefaultSubobject<UPaintCan>(TEXT("RedPaintCan"));
	RedPaintCan->SetupAttachment(RootComponent);	

	GreenPaintCan = CreateDefaultSubobject<UPaintCan>(TEXT("GreenPaintCan"));
	GreenPaintCan->SetupAttachment(RootComponent);
	

}

// Called when the game starts or when spawned
void AColoringMachine::BeginPlay()
{
	Super::BeginPlay();

	if (APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0))
	{
		MarangozPlayerController = Cast<AMarangozPlayerController>(PlayerController);
	}
	
	RedPaintCan->SetColor(FLinearColor(1,0,0));
	GreenPaintCan->SetColor(FLinearColor(0,1,0));

	RedPaintCan->OnPaintCanSelected.AddDynamic(this, &AColoringMachine::OnPaintCanSelected);
	GreenPaintCan->OnPaintCanSelected.AddDynamic(this, &AColoringMachine::OnPaintCanSelected);
}

void AColoringMachine::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	RedPaintCan->SetColor(FLinearColor(1,0,0));
	GreenPaintCan->SetColor(FLinearColor(0,1,0));
}

// Called every frame
void AColoringMachine::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AColoringMachine::OnPaintCanSelected(FLinearColor Color)
{
	if (HasAuthority())
	{
		PaintProductInArea(Color);
	}
	else
	{
		MarangozPlayerController->ServerPaintProductInArea(this,Color);
	}
	

}

void AColoringMachine::PaintProductInArea(FLinearColor Color)
{
	TArray<AActor*> OverlappingActors;
	PaintingArea->GetOverlappingActors(OverlappingActors);

	for (AActor* OverlappingActor : OverlappingActors)
	{
		if (AProductActor* Product = Cast<AProductActor>(OverlappingActor))
		{
			Product->Paint(Color);
		}
	}
}

