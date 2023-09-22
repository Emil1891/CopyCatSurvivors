// Fill out your copyright notice in the Description page of Project Settings.

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
		Iteration = 0;
		NumClaws = 5;
		NumLegs = 4;
		NumTeeth = 30;
		NumTails = 1;
		NumEyes = 2;
		NumHearts = 1;
		Chonkiness = 1;
		BrainSize = 100;
		LungCapacity = 100;
		Name = "Bob";
	}
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Iteration = 0;
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
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Name = "Bob";
	
};

UCLASS()
class COPYCATSURVIVORS_API ACat : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACat();
	ACat(const FCatStruct& CatStruct);

	UFUNCTION(BlueprintImplementableEvent)
	void OnClawAttack();

	UFUNCTION(BlueprintImplementableEvent)
	void OnPounceAttack();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
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

	/** Bool to check if controller is initialized*/
	bool bIsControllerInitialized = false;

	/** Initializes CatBaseAIController*/
	void InitializeController();

	FTimerHandle InitializeControllerTimerHandle;
	float InitializeControllerDelay = 1.f;
};
