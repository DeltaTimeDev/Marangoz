// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProductActor.generated.h"

USTRUCT(BlueprintType)
struct MARANGOZ_API FProductData
{
	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Product")
	FGuid ID;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Product")
	FString Name = "None";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Product")
	UTexture2D* Image = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Product")
	float RawMaterialCost = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Product")
	float Price = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Product")
	UStaticMesh* Mesh = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Product")
	FLinearColor Color = FLinearColor::White;

	FProductData() 
		: ID(FGuid::NewGuid())
	{}
};

UCLASS(Blueprintable)
class MARANGOZ_API UProduct : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Product")
	FProductData Data;
};

UCLASS(BlueprintType)
class MARANGOZ_API UProductDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Product")
	TArray<FProductData> Products;
};


UCLASS()
class MARANGOZ_API AProductActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProductActor();

	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* MeshComponent;

	UPROPERTY(ReplicatedUsing=OnDataChanged)
	FProductData Data;
	
	UFUNCTION()
	void OnDataChanged(FProductData NewData);

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SetProductData(FProductData InData);

	void SetColor(FLinearColor NewColor);
	void Paint(FLinearColor NewColor);

};
