// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemyRatSpawner.generated.h"

// TODO: OBJECT POOLING, ARRAY(?) KEEPING RATS AND WHEN RATS ARE KILLED,
// TODO: THEY END UP IN THE ARRAY INSTEAD OF BEING DESTROYED 

UCLASS()
class COPYCATSURVIVORS_API AEnemyRatSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemyRatSpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:

	int GetWave() const { return WaveCount; }

private:

	UPROPERTY(EditAnywhere, meta=(Units="seconds"))
	float TimeBetweenSpawnWaves = 30.f;

	UPROPERTY()
	class AMapGrid* Grid;

	// Holds the min/max x and y coordinates which are valid spawn points (inside the grid) 
	FVector MinSpawnArea;
	FVector MaxSpawnArea;
	float SpawnZLoc; 

	void SpawnNewWave();

	UPROPERTY(EditAnywhere)
	int StartEnemyCount = 15;

	UPROPERTY(EditAnywhere)
	int EnemyCountIncreaseEachWave = 3;

	int WaveCount = 0;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class ARatCharacter> RatClass;

	UPROPERTY(EditAnywhere, meta=(Units="cm"))
	float MinRangeOutsideScreenToSpawn = 50.f; 

	bool SpawnIsValid(const FVector& SpawnLoc) const;

	bool IsWithinPlayerZone(const FVector& WorldLocation) const; 

	UPROPERTY()
	APlayerController* PlayerController; 

	UPROPERTY()
	FVector2D ViewportSize; 

	// How many tries to spawn an enemy until calling it a failure and ending the spawning altogether
	// Should not be needed by improving the spawning system but time is short 
	UPROPERTY(EditAnywhere)
	int MaxSpawnAttempts = 50;

	UPROPERTY(EditAnywhere)
	float SpawnHeight = 75.f; 
};
