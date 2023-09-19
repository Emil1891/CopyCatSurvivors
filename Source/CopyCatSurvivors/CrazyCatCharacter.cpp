// Fill out your copyright notice in the Description page of Project Settings.


#include "CrazyCatCharacter.h"

#include "Components/WidgetComponent.h"

void ACrazyCatCharacter::BeginPlay()
{
	Super::BeginPlay();

	// Create the HUD widget and add it to player screen 
	HUDWidget = CreateWidget(GetLocalViewingPlayerController(), HUDWidgetClass);
	HUDWidget->AddToPlayerScreen(); 
}

float ACrazyCatCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,
	AActor* DamageCauser)
{
	const float SuperDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	CurrentHealth -= FMath::Min(DamageAmount, CurrentHealth); // decrease health, Min ensures it wont go below zero 

	if(CurrentHealth <= 0)
		KillMe(); 

	return SuperDamage; 
}

void ACrazyCatCharacter::KillMe()
{
	UE_LOG(LogTemp, Warning, TEXT("Player Died"))
}
