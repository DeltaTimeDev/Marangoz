// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/MarangozPlayerController.h"

#include "Gameplay/ColoringMachine.h"
#include "Gameplay/ShapingMachine.h"

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
