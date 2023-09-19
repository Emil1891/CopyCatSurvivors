// Fill out your copyright notice in the Description page of Project Settings.

#include "RatCharacter.h"

// Sets default values
ARatCharacter::ARatCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false; // NOTE: Tick is turned off since it is not needed as of now 
}

// Called when the game starts or when spawned
void ARatCharacter::BeginPlay()
{
	Super::BeginPlay();

	CurrentHealth = MaxHealth; 
}

float ARatCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,
	AActor* DamageCauser)
{
	const float SuperDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	UE_LOG(LogTemp, Warning, TEXT("You damaged a rat! Damage: %f"), DamageAmount)

	CurrentHealth -= FMath::Min(DamageAmount, CurrentHealth);

	if(CurrentHealth <= 0)
		KillMe(); 

	return SuperDamage; 
}

void ARatCharacter::KillMe()
{
	UE_LOG(LogTemp, Warning, TEXT("Rat died"))
}
