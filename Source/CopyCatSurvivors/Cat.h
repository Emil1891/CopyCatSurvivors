// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Cat.generated.h"

class UBlackboardComponent;

USTRUCT()
struct FCatStruct
{
	GENERATED_BODY()
	FCatStruct()
	{
		
	}
	int NumClaws = 5;
	int NumLegs = 4;
	int NumTails = 1;
	int NumEyes = 2;
	int NumHearts = 1;
	int Chonkiness = 1;
	int BrainSize = 100;
	int LungCapacity = 100;
	bool BoneLess = false;
	
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
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
