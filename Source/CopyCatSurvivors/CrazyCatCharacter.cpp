// Fill out your copyright notice in the Description page of Project Settings.


#include "CrazyCatCharacter.h"

#include "Components/WidgetComponent.h"

void ACrazyCatCharacter::BeginPlay()
{
	Super::BeginPlay();

	// Create the HUD widget and add it to player screen 
	HUDWidget = CreateWidget(GetLocalViewingPlayerController(), HUDWidgetClass);
	HUDWidget->AddToPlayerScreen();

	CurrentHealth = InitialHealth;
}

float ACrazyCatCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,
	AActor* DamageCauser)
{
	const float SuperDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	// if not enough time has passed since last taking damage, then dont do damage 
	if(GetWorld()->GetTimeSeconds() - LastDamageTime < GracePeriod)
		return SuperDamage;
	
	// decrease health, Min ensures it wont go below zero 
	CurrentHealth -= FMath::Min(DamageAmount, CurrentHealth); 

	if(CurrentHealth <= 0)
		KillMe();

	LastDamageTime = GetWorld()->GetTimeSeconds();

	UE_LOG(LogTemp, Warning, TEXT("Health: %f"), CurrentHealth)

	return SuperDamage; 
}

void ACrazyCatCharacter::KillMe()
{
	OnKillMeEvent();
	UE_LOG(LogTemp, Warning, TEXT("Player Died"))
}

void ACrazyCatCharacter::LeveledUp()
{
	// TODO: ADD ALL LEVEL UP STUFF HERE 
	
	XPLevel++; 
	CurrentXP = 0; // Reset
	XPToLevelUp *= XPMultiplierEachLevel; // Multiply so more xp is needed next level

	// TODO: Probably freeze game and display level up UI screen
	LevelUpEvent();
}

void ACrazyCatCharacter::IncreaseXP(const int XPIncrease)
{
	// add xp 
	CurrentXP += XPIncrease;

	// see if added xp made player level up 
	if(CurrentXP >= XPToLevelUp)
		LeveledUp();
	else // if not, then trigger event that signals increased xp 
		OnIncreasedXP(); 
}
