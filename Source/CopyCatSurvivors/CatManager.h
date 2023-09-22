// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CatManager.generated.h"

class ACrazyCatCharacter;
struct FCatStruct;
class ACat;
class UPaperFlipbookComponent;

UENUM()
enum PropertyType
{
	NumLegs, NumClaws, NumTeeth, NumTails, NumEyes, NumHearts, LungCapacity, BrainSize, Chonkiness
};

USTRUCT()
struct FWeightedAndValuedProperty
{
	FWeightedAndValuedProperty()
	{
		Type = TEnumAsByte<PropertyType>();
		Weight = -1;
		IncreaseValue = -1.0f;
		DecreaseValue = -1.0f;
	}
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

	UPROPERTY(BlueprintReadWrite)
	TArray<FString> Names;

	UPROPERTY(EditAnywhere)
	TArray<FWeightedAndValuedProperty> WeightedPropertiesArray;

	UFUNCTION(BlueprintCallable)
	FCatStruct Copy(FCatStruct CopyCat);

	UFUNCTION(BlueprintCallable)
	FCatStruct Mutate(FCatStruct CatStruct);

	UFUNCTION(BlueprintCallable)
	FCatStruct Splice(FCatStruct Cat1, FCatStruct Cat2);

	UFUNCTION(BlueprintCallable)
	FCatStruct Fuse(FCatStruct Cat1, FCatStruct Cat2);

	UFUNCTION(BlueprintCallable)
	void SpawnCat(FCatStruct NewCatStruct);

private:
	int TotalWeight = 0;
	void ChangeRandomProperty(FCatStruct& Cat, const double Multiplier);

	/** Calculates spawn location based on player characters position in world space*/
	void CalculateSpawnLocations();

	/** Spawns cat instances*/
	void SpawnStartingCats();

	/** Decides how many cats to spawn*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Spawning, meta=(AllowPrivateAccess = "true"))
	int NumOfInitialCats = 1.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Spawning, meta=(AllowPrivateAccess = "true"))
	TSubclassOf<ACat> CatClass;

	/** Pointer to player character, used for spawning and setting target*/
	ACrazyCatCharacter* PlayerCharacter;

	/** Location in worlds pace toward which cats are supposed to move*/
	FVector SpawnLocation = FVector::ZeroVector;

	/** Distance between cats spawning location*/
	float DistanceBetweenCats = 100.f;

	/** List of spawn location*/
	TArray<FVector> SpawnLocations = TArray<FVector>();

	int CalcCatIteration(FCatStruct CatStruct);
	
};

