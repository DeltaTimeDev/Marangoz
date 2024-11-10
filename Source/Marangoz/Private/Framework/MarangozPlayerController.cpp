// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/MarangozPlayerController.h"

#include "Blueprint/UserWidget.h"
#include "Gameplay/Machines/ColoringMachine.h"
#include "Gameplay/Machines/ShapingMachine.h"
#include "Gameplay/Subsystem/MoneySubsystem.h"
#include "Widgets/MainWidget.h"


void AMarangozPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (IsLocalController())
	{
		if (UUserWidget* MainWidget =  CreateWidget(this,MainWidgetClass))
		{
			MainWidget->AddToViewport();
			MainWidgetRef = Cast<UMainWidget>(MainWidget);
		}
		if (UMoneySubsystem* MoneySubsystem = Cast<UMoneySubsystem>(GetGameInstance()->GetSubsystem<UMoneySubsystem>()))
		{
			MoneySubsystem->OnMoneyChanged.AddDynamic(this, &AMarangozPlayerController::OnMoneyChanged);
			if (IsValid(MainWidgetRef))
			{
				MainWidgetRef->SetMoney(MoneySubsystem->MoneyCount);
			}
		}
	}
	

	

}

void AMarangozPlayerController::OnMoneyChanged(int32 NewMoneyValue)
{
	MainWidgetRef->SetMoney(NewMoneyValue);

	for (FConstControllerIterator It = GetWorld()->GetControllerIterator(); It; ++It)
	{
		AController* Controller = It->Get();
		if (Controller)
		{
			if (AMarangozPlayerController* PlayerController = Cast<AMarangozPlayerController>(Controller))
			{
				PlayerController->ClientSetMoney(NewMoneyValue);
			}
		}
	}
}

void AMarangozPlayerController::ClientSetMoney_Implementation(int32 NewMoney)
{
	MainWidgetRef->SetMoney(NewMoney);
}

void AMarangozPlayerController::ServerSetProductShapingMachine_Implementation(AShapingMachine* ShapingMachine, FGuid SelectedProductID)
{
	ShapingMachine->SetSelectedProductOnServer(SelectedProductID);
}

void AMarangozPlayerController::ServerSpawnProduct_Implementation(AShapingMachine* ShapingMachine)
{
	ShapingMachine->SpawnProduct();
}

void AMarangozPlayerController::ServerPaintProductInArea_Implementation(AColoringMachine* ColorMachine,
	FLinearColor Color)
{
	ColorMachine->PaintProductInArea(Color);
}


