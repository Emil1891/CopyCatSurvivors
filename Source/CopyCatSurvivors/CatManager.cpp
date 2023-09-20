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

	for(const FWeightedAndValuedProperty Property : WeightedPropertiesArray)
	{
		TotalWeight += Property.Weight;
	}
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

FCatStruct ACatManager::Splice(FCatStruct Cat1, FCatStruct Cat2)
{
	FCatStruct NewCat;
	for(const FWeightedAndValuedProperty Property : WeightedPropertiesArray)
	{
		switch (Property.Type)
		{
		case NumClaws:
			NewCat.NumClaws = rand() % 2 == 0 ? Cat1.NumClaws : Cat2.NumClaws;
			break;
		case NumLegs:
			NewCat.NumLegs = rand() % 2 == 0 ? Cat1.NumLegs : Cat2.NumLegs;
			break;
		case NumTeeth:
			NewCat.NumTeeth = rand() % 2 == 0 ? Cat1.NumTeeth : Cat2.NumTeeth;
			break;
		case NumTails:
			NewCat.NumTails = rand() % 2 == 0 ? Cat1.NumTails : Cat2.NumTails;
			break;
		case NumEyes:
			NewCat.NumEyes = rand() % 2 == 0 ? Cat1.NumEyes : Cat2.NumEyes;
			break;
		case NumHearts:
			NewCat.NumHearts = rand() % 2 == 0 ? Cat1.NumHearts : Cat2.NumHearts;
			break;
		case LungCapacity:
			NewCat.LungCapacity = rand() % 2 == 0 ? Cat1.LungCapacity : Cat2.LungCapacity;
			break;
		case BrainSize:
			NewCat.BrainSize = rand() % 2 == 0 ? Cat1.BrainSize : Cat2.BrainSize;
			break;
		case Chonkiness:
			NewCat.Chonkiness = rand() % 2 == 0 ? Cat1.Chonkiness : Cat2.Chonkiness;
			break;
		default:
			break;
		}
		break;
	}
	return NewCat;
}

FCatStruct ACatManager::Fuse(FCatStruct Cat1, FCatStruct Cat2)
{
	FCatStruct NewCat;
	for(const FWeightedAndValuedProperty Property : WeightedPropertiesArray)
	{
		switch (Property.Type)
		{
		case NumClaws:
			NewCat.NumClaws = abs(Cat1.NumClaws - NewCat.NumClaws) > abs(Cat2.NumClaws - NewCat.NumClaws) ? Cat1.NumClaws : Cat2.NumClaws;
			break;
		case NumLegs:
			NewCat.NumLegs = abs(Cat1.NumLegs - NewCat.NumLegs) > abs(Cat2.NumLegs - NewCat.NumLegs) ? Cat1.NumLegs : Cat2.NumLegs;
			break;
		case NumTeeth:
			NewCat.NumTeeth = abs(Cat1.NumTeeth - NewCat.NumTeeth) > abs(Cat2.NumTeeth - NewCat.NumTeeth) ? Cat1.NumTeeth : Cat2.NumTeeth;
			break;
		case NumTails:
			NewCat.NumTails = abs(Cat1.NumTails - NewCat.NumTails) > abs(Cat2.NumTails - NewCat.NumTails) ? Cat1.NumTails : Cat2.NumTails;
			break;
		case NumEyes:
			NewCat.NumEyes = abs(Cat1.NumEyes - NewCat.NumEyes) > abs(Cat2.NumEyes - NewCat.NumEyes) ? Cat1.NumEyes : Cat2.NumEyes;
			break;
		case NumHearts:
			NewCat.NumHearts = abs(Cat1.NumHearts - NewCat.NumHearts) > abs(Cat2.NumHearts - NewCat.NumHearts) ? Cat1.NumHearts : Cat2.NumHearts;
			break;
		case LungCapacity:
			NewCat.LungCapacity = abs(Cat1.LungCapacity - NewCat.LungCapacity) > abs(Cat2.LungCapacity - NewCat.LungCapacity) ? Cat1.LungCapacity : Cat2.LungCapacity;
			break;
		case BrainSize:
			NewCat.BrainSize = abs(Cat1.BrainSize - NewCat.BrainSize) > abs(Cat2.BrainSize - NewCat.BrainSize) ? Cat1.BrainSize : Cat2.BrainSize;
			break;
		case Chonkiness:
			NewCat.Chonkiness = abs(Cat1.Chonkiness - NewCat.Chonkiness) > abs(Cat2.Chonkiness - NewCat.Chonkiness) ? Cat1.Chonkiness : Cat2.Chonkiness;
			break;
		default:
			break;
		}
		break;
	}
	ChangeRandomProperty(NewCat, 3);
	ChangeRandomProperty(NewCat, 2);
	ChangeRandomProperty(NewCat, 1);
	ChangeRandomProperty(NewCat, -1);
	ChangeRandomProperty(NewCat, -1);
	return NewCat;
}

void ACatManager::ChangeRandomProperty(FCatStruct& Cat, const double Multiplier)
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
				Cat.LungCapacity += Property.IncreaseValue * Multiplier;
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
		WeightIndex -= Property.Weight;
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
