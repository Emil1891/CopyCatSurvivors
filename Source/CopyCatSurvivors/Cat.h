﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Cat.generated.h"

class UBlackboardComponent;

USTRUCT(BlueprintType)
struct FCatStruct
{
	GENERATED_BODY()
	FCatStruct()
	{
		
	}
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	double NumClaws = 5;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	double NumLegs = 4;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	double NumTeeth = 30;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	double NumTails = 1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	double NumEyes = 2;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	double NumHearts = 1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	double Chonkiness = 1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	double BrainSize = 100;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	double LungCapacity = 100;
	
};

UCLASS()
class COPYCATSURVIVORS_API ACat : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACat();
	ACat(const FCatStruct& CatStruct);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:

	UPROPERTY(EditAnywhere)
	FCatStruct Properties;

	UPROPERTY(EditAnywhere)
	UBlackboardComponent* BlackboardComponent = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	double Mass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	double MoveSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	double AttackSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	double BiteDamage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	double ClawDamage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	double PounceDamage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	double PounceDistance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	double TrackingAccuracy;

	UFUNCTION(BlueprintCallable)
	void UpdateDerivedProperties();
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
