// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CatManager.generated.h"

struct FCatStruct;
class ACat;

UENUM()
enum PropertyType
{
	NumLegs, NumClaws, NumTeeth, NumTails, NumEyes, NumHearts, LungCapacity, BrainSize, Chonkiness
};

USTRUCT()
struct FWeightedAndValuedProperty
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere)
	TEnumAsByte<PropertyType> Type;
	UPROPERTY(EditAnywhere)
	int Weight;
	UPROPERTY(EditAnywhere)
	double IncreaseValue;
	UPROPERTY(EditAnywhere)
	double DecreaseValue;
};

UCLASS()
class COPYCATSURVIVORS_API ACatManager : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ACatManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(BlueprintReadWrite)
	TArray<ACat*> Cats;

	UPROPERTY(EditAnywhere)
	TArray<FWeightedAndValuedProperty> WeightedPropertiesArray;

	UFUNCTION(BlueprintCallable)
	FCatStruct Copy(FCatStruct CopyCat);

	UFUNCTION(BlueprintCallable)
	void Mutate(FCatStruct& CatStruct);

private:
	int TotalWeight = 0;
	void ChangeRandomProperty(FCatStruct& Cat, double Multiplier);
};

