// Fill out your copyright notice in the Description page of Project Settings.

#include "RatCharacter.h"

#include "EnemyRatSpawner.h"
#include "XPDrop.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Engine/UserInterfaceSettings.h"
#include "Kismet/GameplayStatics.h"

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

	if(!Spawner)
		Spawner = Cast<AEnemyRatSpawner>(UGameplayStatics::GetActorOfClass(this, AEnemyRatSpawner::StaticClass())); 

	// set health based on wave, increasing it with time
	if(Spawner)
		CurrentHealth = InitialMaxHealth + HealthIncreaseEachSpawnWave * Spawner->GetWave();
	else // Should not get here but might when debugging in test maps without a spawner 
		CurrentHealth = InitialMaxHealth; 
}

float ARatCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,
                                AActor* DamageCauser)
{
	const float SuperDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	UE_LOG(LogTemp, Warning, TEXT("You damaged a rat! Damage: %f"), DamageAmount)

	CurrentHealth -= FMath::Min(DamageAmount, CurrentHealth);

	if(CurrentHealth <= 0)
		KillMe();
	else
		ShowDamageNumberUI(DamageAmount);

	return SuperDamage; 
}

void ARatCharacter::KillMe()
{
	UE_LOG(LogTemp, Warning, TEXT("Rat died"))

	// drop xp drop 
	if(XPDropClass)
		GetWorld()->SpawnActor<AActor>(XPDropClass, GetActorLocation(), FRotator::ZeroRotator); 

	// TODO: Object pooling for the spawner instead of destroying (if time) 
	Destroy();
}

void ARatCharacter::ShowDamageNumberUI(const float DamageAmount) const
{
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);
	
	// Create a new widget 
	UUserWidget* DamageWidget = CreateWidget(PlayerController, DamageWidgetClass); 
	
	// get screen bounds 
	int32 ScreenWidth, ScreenHeight;
	PlayerController->GetViewportSize(ScreenWidth, ScreenHeight);

	// Source to get DPI Scale: https://forums.unrealengine.com/t/current-dpi-scaling/296699/3 
	const float ScaleDPI = GetDefault<UUserInterfaceSettings>(UUserInterfaceSettings::StaticClass())->
		GetDPIScaleBasedOnSize(FIntPoint(ScreenWidth, ScreenHeight));

	// Get the rat's screen pos 
	FVector2D ScreenLocation; 
	PlayerController->ProjectWorldLocationToScreen(GetActorLocation(), ScreenLocation);

	// Math to take different resolutions into account, should now always be shown where the rat is
	// Reason why it is needed as I understand it: 
	// Unreal uses so called Slate Units for its UI position system and 1 slate unit is different sized based on the 
	// resolution, so need to take it into account to make sure the widget is positioned the same across all screens  
	ScreenLocation /= ScaleDPI; // Converts to Slate Units 

	// Get the text widget, update its text with the damage amount, set its position 
	UWidget* DamageNumberWidget = DamageWidget->GetWidgetFromName(FName("DamageNumber"));
	Cast<UTextBlock>(DamageNumberWidget)->SetText(FText::AsNumber(DamageAmount)); 
	DamageNumberWidget->SetRenderTranslation(ScreenLocation);

	// Add to player screen  
	DamageWidget->AddToPlayerScreen();

	// Removal is handled by the widget itself 
}
