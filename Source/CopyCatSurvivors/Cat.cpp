// Fill out your copyright notice in the Description page of Project Settings.


#include "Cat.h"

#include "CatBaseAIController.h"
#include "BehaviorTree/BlackboardComponent.h"


// Sets default values
ACat::ACat()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	BlackboardComponent = CreateDefaultSubobject<UBlackboardComponent>(TEXT("Blackboard"));
	InitializeController();
}


ACat::ACat(const FCatStruct& CatStruct)
{
	Properties = CatStruct;
	ACat();
}


// Called when the game starts or when spawned
void ACat::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACat::UpdateDerivedProperties()
{
	Mass = Properties.Chonkiness + (Properties.NumLegs - 4) + (Properties.NumTails - 1) + Properties.BrainSize/100;
	//Fyll på med resten av derived properties
}

// Called every frame
void ACat::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ACat::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ACat::InitializeController()
{
	if(bIsControllerInitialized) return;
	bIsControllerInitialized = true;
	ACatBaseAIController* AIController = Cast<ACatBaseAIController>(GetController());
	if(AIController)
	{
		UE_LOG(LogTemp, Warning, TEXT("HAsController"));

		AIController->Initialize();
	}
}

