// Fill out your copyright notice in the Description page of Project Settings.


#include "CatManager.h"
#include "Cat.h"
#include "CrazyCatCharacter.h"
#include "Kismet/GameplayStatics.h"

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

	PlayerCharacter = Cast<ACrazyCatCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (PlayerCharacter)
	{
		//set target location
	}
	SpawnCats();
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

void ACatManager::CalculateSpawnLocations()
{
	FVector InitialSpawnLocation = PlayerCharacter->GetActorLocation() + DistanceBetweenCats;
	if(NumOfInitialCats == 1)
	{
		SpawnLocations.Add(InitialSpawnLocation);
	}
	else if(NumOfInitialCats == 2)
	{
		SpawnLocations.Add(FVector(InitialSpawnLocation.X, InitialSpawnLocation.Y  + DistanceBetweenCats, InitialSpawnLocation.Z));
		SpawnLocations.Add(InitialSpawnLocation);
	}
	else if(NumOfInitialCats == 3)
	{
		SpawnLocations.Add(InitialSpawnLocation);
		SpawnLocations.Add(FVector (InitialSpawnLocation.X + DistanceBetweenCats * FMath::Cos(60.f), InitialSpawnLocation.Y + DistanceBetweenCats * FMath::Sin(60.f), InitialSpawnLocation.Z ));
		SpawnLocations.Add(FVector (InitialSpawnLocation.X + DistanceBetweenCats * FMath::Cos(-60.f), InitialSpawnLocation.Y + DistanceBetweenCats * FMath::Sin(-60.f), InitialSpawnLocation.Z ));
	}
	else if(NumOfInitialCats == 4)
	{
		SpawnLocations.Add(FVector(InitialSpawnLocation.X - DistanceBetweenCats, InitialSpawnLocation.Y - DistanceBetweenCats,  InitialSpawnLocation.Z ));
		SpawnLocations.Add(FVector(InitialSpawnLocation.X - DistanceBetweenCats, InitialSpawnLocation.Y + DistanceBetweenCats,  InitialSpawnLocation.Z ));
		SpawnLocations.Add(FVector(InitialSpawnLocation.X + DistanceBetweenCats, InitialSpawnLocation.Y + DistanceBetweenCats,  InitialSpawnLocation.Z ));
		SpawnLocations.Add(FVector(InitialSpawnLocation.X + DistanceBetweenCats, InitialSpawnLocation.Y - DistanceBetweenCats,  InitialSpawnLocation.Z ));
	}
}

void ACatManager::SpawnCats()
{
	if (!GetWorld()) return;
	if (NumOfInitialCats != 0)
	{		
		CalculateSpawnLocations();
	
		for (FVector Loc : SpawnLocations)
		{
			FActorSpawnParameters SpawnParams;
			SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	
			ACat* NewCat = GetWorld()->SpawnActor<ACat>(CatClass, Loc, FRotator::ZeroRotator, SpawnParams);
			ensure (NewCat != nullptr);
	
			// create struct with data, set variables in struct, assign pointer in spawned cat to that struct in array and add both cat and struct in collections
			Cats.Add(NewCat);
		}
	}
}
