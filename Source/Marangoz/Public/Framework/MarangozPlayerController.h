// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MarangozPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class MARANGOZ_API AMarangozPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	UFUNCTION(Server,Reliable)
	void ServerSetProductShapingMachine(class AShapingMachine* ShapingMachine, FGuid SelectedProductID);

	UFUNCTION(Server,Reliable)
	void ServerSpawnProduct(class AShapingMachine* ShapingMachine);

	UFUNCTION(Server,Reliable)
	void ServerPaintProductInArea(class AColoringMachine* ColorMachine, FLinearColor Color);

};
