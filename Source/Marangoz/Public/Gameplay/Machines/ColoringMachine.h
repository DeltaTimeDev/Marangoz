// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MachineBase.h"
#include "ColoringMachine.generated.h"



UCLASS()
class MARANGOZ_API AColoringMachine : public AMachineBase
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AColoringMachine();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void OnConstruction(const FTransform& Transform) override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnPaintCanSelected(FLinearColor Color);

	void PaintProductInArea(FLinearColor Color);

	UPROPERTY(VisibleAnywhere, Category="Components")
	class UBoxComponent* PaintingArea;

	UPROPERTY(VisibleAnywhere, Category="Components")
	class UPaintCan* RedPaintCan;

	UPROPERTY(VisibleAnywhere, Category="Components")
	UPaintCan* GreenPaintCan;

	UPROPERTY()
	class AMarangozPlayerController* MarangozPlayerController;

};
