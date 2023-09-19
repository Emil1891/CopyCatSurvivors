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

	const FVector GridLocation = Grid->GetActorLocation(); 
	SpawnZLoc = GridLocation.Z;

	// Set minimum coordinates where spawns are valid 
	MinSpawnArea = Grid->GetGridBottomLeftLocation();

	// Set max coordinates where spawns are valid 
	const FVector2D GridSize = Grid->GetGridSize();
	MaxSpawnArea = MinSpawnArea;
	MaxSpawnArea.X += GridSize.X;
	MaxSpawnArea.Y += GridSize.Y; 

	GetWorld()->GetTimerManager().SetTimerForNextTick(this, &AEnemyRatSpawner::SpawnNewWave); 
}

void AEnemyRatSpawner::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	GetWorld()->GetTimerManager().ClearAllTimersForObject(this); 
}

void AEnemyRatSpawner::SpawnNewWave()
{
	const int EnemiesToSpawn = StartEnemyCount + WaveCount * EnemyCountIncreaseEachWave;
	
	UE_LOG(LogTemp, Warning, TEXT("Spawning new wave, enemy count: %i"), EnemiesToSpawn)
	
	for(int i = 0; i < EnemiesToSpawn; i++)
	{
		FVector SpawnLoc = FVector::Zero();
		SpawnLoc.Z = SpawnZLoc; 
		
		// TODO: CHECK SO SPAWN LOC IS NOT ON PLAYER SCREEN
		do
		{
			SpawnLoc.X = FMath::RandRange(MinSpawnArea.X, MaxSpawnArea.X); 
			SpawnLoc.Y = FMath::RandRange(MinSpawnArea.Y, MaxSpawnArea.Y);
		} while(!Grid->GetNodeFromWorldLocation(SpawnLoc)->IsWalkable()); // Generate new spawn point if spawn point is unwalkable 
		
		GetWorld()->SpawnActor<AActor>(RatClass, SpawnLoc, FRotator::ZeroRotator); 
	}

	WaveCount++;

	// Set timer for when to spawn a new wave 
	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AEnemyRatSpawner::SpawnNewWave, TimeBetweenSpawnWaves); 
}
