// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/MarangozPlayerController.h"

#include "Gameplay/ShapingMachine.h"

void AMarangozPlayerController::ServerSetProductShapingMachine_Implementation(AShapingMachine* ShapingMachine, FGuid SelectedProductID)
{
	ShapingMachine->SetSelectedProductOnServer(SelectedProductID);
}

void AMarangozPlayerController::ServerSpawnProduct_Implementation(AShapingMachine* ShapingMachine)
{
	ShapingMachine->SpawnProduct();
}
