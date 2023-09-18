// Fill out your copyright notice in the Description page of Project Settings.


#include "CatManager.h"
#include "Cat.h"

// Sets default values
ACatManager::ACatManager()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Cats = TArray<ACat*>();
}

// Called when the game starts or when spawned
void ACatManager::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACatManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

FCatStruct ACatManager::Copy(FCatStruct CopyCat)
{
	FCatStruct NewCat = CopyCat;
	ChangeRandomProperty(NewCat, 2);
	ChangeRandomProperty(NewCat, 1);
	ChangeRandomProperty(NewCat, -1);
	return NewCat;
}

void ACatManager::Mutate(FCatStruct& CatStruct)
{
	ChangeRandomProperty(CatStruct, 3);
	ChangeRandomProperty(CatStruct, 2);
	ChangeRandomProperty(CatStruct, 1);
	ChangeRandomProperty(CatStruct, -1);
	ChangeRandomProperty(CatStruct, -1);
}

void ACatManager::ChangeRandomProperty(FCatStruct& Cat, double Multiplier)
{
	int WeightIndex = rand() % TotalWeight;
	for(const FWeightedAndValuedProperty Property : WeightedPropertiesArray)
	{
		if(WeightIndex <= Property.Weight)
		{
			switch (Property.Type)
			{
			case NumClaws:
				Cat.NumClaws += Property.IncreaseValue * Multiplier;
				break;
			case NumLegs:
				Cat.NumLegs += Property.IncreaseValue * Multiplier;
				break;
			case NumTeeth:
				Cat.NumTeeth += Property.IncreaseValue * Multiplier;
				break;
			case NumTails:
				Cat.NumTails += Property.IncreaseValue * Multiplier;
				break;
			case NumEyes:
				Cat.NumEyes += Property.IncreaseValue * Multiplier;
				break;
			case NumHearts:
				Cat.NumHearts += Property.IncreaseValue * Multiplier;
				break;
			case LungCapacity:
				Cat.NumClaws += Property.IncreaseValue * Multiplier;
				break;
			case BrainSize:
				Cat.BrainSize += Property.IncreaseValue * Multiplier;
				break;
			case Chonkiness:
				Cat.Chonkiness += Property.IncreaseValue * Multiplier;
				break;
			default:
				break;
			}
			break;
		}
		else
		{
			WeightIndex -= Property.Weight;
		}
	}
}