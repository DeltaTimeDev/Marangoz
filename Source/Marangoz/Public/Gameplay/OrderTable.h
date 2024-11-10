// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "OrderTable.generated.h"

UCLASS()
class MARANGOZ_API AOrderTable : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AOrderTable();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, Category="Components")
	UStaticMeshComponent* MeshComponent;
	
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class AOrderActor> OrderActorsClass;

	UPROPERTY(EditDefaultsOnly)
	TArray<FName> SpawnPointSocketNames;

	UPROPERTY()
	TArray<AOrderActor*> OrderActors;

	void SpawnOrderActor(FName SocketName);

	void OnOrderTimerTicks();
	
	FTimerHandle OrderTimer;

	
	UPROPERTY(EditAnywhere)
	class UProductDataAsset* ProductDataAsset;

	FLinearColor GetRandomColor();

	TArray<FLinearColor> Colors { FLinearColor::Red, FLinearColor::Green};
	
};
