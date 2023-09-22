// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "RatCharacter.generated.h"

UCLASS()
class COPYCATSURVIVORS_API ARatCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ARatCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	

	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	// Need access in RatSpawner
	inline static class AEnemyRatSpawner* Spawner = nullptr;
	
private:
	UPROPERTY(EditAnywhere)
	int InitialMaxHealth = 10;

	UPROPERTY(EditAnywhere)
	int HealthIncreaseEachSpawnWave = 2; 

	int CurrentHealth;

	void KillMe();

	void ShowDamageNumberUI(const float DamageAmount) const; 

	UPROPERTY(EditAnywhere)
	TSubclassOf<class AXPDrop> XPDropClass;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> DamageWidgetClass;
	
	UPROPERTY(EditAnywhere)
	float TimeToRemoveDamageUI = 1.f;
};
