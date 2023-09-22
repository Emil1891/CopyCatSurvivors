// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemyRatSpawner.h"

#include "MapGrid.h"
#include "RatCharacter.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AEnemyRatSpawner::AEnemyRatSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void AEnemyRatSpawner::BeginPlay()
{
	Super::BeginPlay();

	Grid = Cast<AMapGrid>(UGameplayStatics::GetActorOfClass(this, AMapGrid::StaticClass()));

	if(!Grid)
	{
		UE_LOG(LogTemp, Error, TEXT("Could not find grid, is there a grid in level?"))
		return; 
	}

	SpawnZLoc = SpawnHeight;

	// Set minimum coordinates where spawns are valid 
	MinSpawnArea = Grid->GetGridBottomLeftLocation();

	// Set max coordinates where spawns are valid 
	const FVector2D GridSize = Grid->GetGridSize();
	MaxSpawnArea = MinSpawnArea;
	MaxSpawnArea.X += GridSize.X;
	MaxSpawnArea.Y += GridSize.Y;

	PlayerController = UGameplayStatics::GetPlayerController(this, 0);

	// Used later to prevent enemies from spawning on the players screen 
	int x, y; 
	PlayerController->GetViewportSize(x, y);
	ViewportSize = FVector2D(x, y); 

	// Delayed to ensure Grid is set up before spawning enemies 
	GetWorld()->GetTimerManager().SetTimerForNextTick(this, &AEnemyRatSpawner::SpawnNewWave); 
}

void AEnemyRatSpawner::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	GetWorld()->GetTimerManager().ClearAllTimersForObject(this);

	ARatCharacter::Spawner = nullptr; 
}

void AEnemyRatSpawner::SpawnNewWave()
{
	const int EnemiesToSpawn = StartEnemyCount + WaveCount * EnemyCountIncreaseEachWave;
	
	UE_LOG(LogTemp, Warning, TEXT("Spawning new wave, enemies spawning: %i"), EnemiesToSpawn)
	
	for(int i = 0; i < EnemiesToSpawn; i++)
	{
		FVector SpawnLoc = FVector::Zero();
		SpawnLoc.Z = SpawnZLoc; 

		// TODO: Improve this, maybe spread the spawns out over frames?
		int SpawnAttempts = 0; 
		do
		{
			if(SpawnAttempts++ > MaxSpawnAttempts)
			{
				UE_LOG(LogTemp, Warning, TEXT("failed too many spawns"))
				goto breakpoint; // now this is programming
			}
			
			SpawnLoc.X = FMath::RandRange(MinSpawnArea.X, MaxSpawnArea.X); 
			SpawnLoc.Y = FMath::RandRange(MinSpawnArea.Y, MaxSpawnArea.Y);
		} while(!SpawnIsValid(SpawnLoc) && SpawnAttempts < 100); // Generate new spawn point if spawn is not valid 
		
		GetWorld()->SpawnActor<AActor>(RatClass, SpawnLoc, FRotator::ZeroRotator); 
	}

	breakpoint: 
	
	WaveCount++;

	// Set timer for when to spawn a new wave 
	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AEnemyRatSpawner::SpawnNewWave, TimeBetweenSpawnWaves); 
}

// TODO: PROBABLY REPLACE THIS WITH BETTER CONSTRAINTS WHEN RANDOMIZING SPAWN LOCATION, OR AT LEAST A COMBINATION 
bool AEnemyRatSpawner::SpawnIsValid(const FVector& SpawnLoc) const
{
	// if spawn location is inside an unwalkable node, it is not valid 
	if(!Grid->GetNodeFromWorldLocation(SpawnLoc)->IsWalkable())
		return false;

	// if enemy would spawn on players screen, then it is not valid 
	if(IsWithinPlayerZone(SpawnLoc))
		return false; 

	return true; 
}

bool AEnemyRatSpawner::IsWithinPlayerZone(const FVector& WorldLocation) const
{
	FVector2D ScreenLocation; 
	PlayerController->ProjectWorldLocationToScreen(WorldLocation, ScreenLocation);

	return ScreenLocation.X > -MinRangeOutsideScreenToSpawn &&
		ScreenLocation.X < ViewportSize.X + MinRangeOutsideScreenToSpawn &&
			ScreenLocation.Y > -MinRangeOutsideScreenToSpawn &&
				ScreenLocation.Y < ViewportSize.Y + MinRangeOutsideScreenToSpawn; 
}
