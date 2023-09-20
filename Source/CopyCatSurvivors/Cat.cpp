// Fill out your copyright notice in the Description page of Project Settings.


#include "Cat.h"

#include "CatBaseAIController.h"
#include "BehaviorTree/BlackboardComponent.h"


// Sets default values
ACat::ACat()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	//BlackboardComponent = CreateDefaultSubobject<UBlackboardComponent>(TEXT("Blackboard"));
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

	UpdateDerivedProperties();
	
	GetWorldTimerManager().SetTimer(InitializeControllerTimerHandle, this, &ACat::InitializeController, 0.1, false, InitializeControllerDelay);
}

void ACat::UpdateDerivedProperties()
{
	Mass = Properties.Chonkiness + (Properties.NumLegs - 4) / 4 + (Properties.NumTails - 1) / 4 + Properties.BrainSize/100; //2 by default
	MoveSpeed = (Properties.NumLegs - Mass) * 100 + 100; //300 by default
	AttackSpeed = Properties.LungCapacity / 25 + Properties.NumHearts * 2 - Mass; //4 by default
	BiteDamage = Properties.NumTeeth; //30 by default
	ClawDamage = Properties.NumLegs * Properties.NumClaws; //20 by default
	PounceDamage = Mass * 20 + (BiteDamage + ClawDamage) / 2; //65 by default
	PounceDistance = 300 + Properties.NumTails * 100 - Mass * 50; //300 by default
	TrackingAccuracy = Properties.BrainSize * Properties.NumEyes; //200 by default
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

