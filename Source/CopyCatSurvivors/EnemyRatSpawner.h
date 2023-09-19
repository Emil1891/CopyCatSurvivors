// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemyRatSpawner.generated.h"

// TODO: OBJECT POOLING, ARRAY(?) KEEPING RATS AND WHEN RATS ARE KILLED
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

};
