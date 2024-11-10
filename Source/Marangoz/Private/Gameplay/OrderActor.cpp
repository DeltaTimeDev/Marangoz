// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/OrderActor.h"

#include "Components/BoxComponent.h"
#include "Components/TextRenderComponent.h"
#include "Gameplay/ProductActor.h"
#include "Gameplay/Subsystem/MoneySubsystem.h"
#include "Net/UnrealNetwork.h"

// Sets default values
AOrderActor::AOrderActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	bReplicates = true;

	RootComp = CreateDefaultSubobject<USceneComponent>(TEXT("RootComp"));
	RootComponent = RootComp;
	
	AcceptingArea = CreateDefaultSubobject<UBoxComponent>(TEXT("PaintingArea"));
	AcceptingArea->SetupAttachment(RootComponent);
	AcceptingArea->SetHiddenInGame(false);
	

	TextRenderComponent = CreateDefaultSubobject<UTextRenderComponent>(TEXT("TextRenderComponent"));
	TextRenderComponent->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void AOrderActor::BeginPlay()
{
	Super::BeginPlay();

	if (HasAuthority())
	{
		AcceptingArea->OnComponentBeginOverlap.AddDynamic(this, &AOrderActor::OnOverlapBegin);
	}
	UpdateVisual();
}

void AOrderActor::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AOrderActor, Order)
}

// Called every frame
void AOrderActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void AOrderActor::SetOrder(FOrder InOrder)
{
	Order = InOrder;
	UpdateVisual();
}

void AOrderActor::OnOrderChanged(FOrder NewOrder)
{
	UpdateVisual();
}

void AOrderActor::Activate(bool Value)
{
	TextRenderComponent->SetVisibility(Value);
	AcceptingArea->SetVisibility(Value);
}

void AOrderActor::UpdateVisual()
{
	Activate(Order.IsActive);
	FString Text = ColorNameMap[Order.Color];
	Text.Append(" ").Append(Order.Name);
	TextRenderComponent->SetText(Text);
}

void AOrderActor::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
                                 UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{


	if (UMoneySubsystem* MoneySubsystem = Cast<UMoneySubsystem>(GetGameInstance()->GetSubsystem<UMoneySubsystem>()))
	{
		if (AProductActor* ProductActor = Cast<AProductActor>(OtherActor))
		{
			FProductData Data = ProductActor->Data;
			if (Data.ID == Order.ID)
			{
				if (Data.Color == Order.Color)
				{
					UE_LOG(LogTemp, Warning, TEXT("Order type and color is correct"));
					MoneySubsystem->Earn(Data.Price);
				}
				else
				{
					UE_LOG(LogTemp, Warning, TEXT("Order type is correct color is wrong"));
					MoneySubsystem->Earn(Data.Price / 2);
				}
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("Order type is wrong"));
				MoneySubsystem->Earn(0);
			}

			ProductActor->Destroy();
			Order.IsActive = false;
			SetOrder(Order);
		}
	}
}

