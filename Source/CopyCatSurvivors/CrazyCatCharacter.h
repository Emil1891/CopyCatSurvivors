// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CopyCatSurvivorsCharacter.h"
#include "CrazyCatCharacter.generated.h"

/**
 * 
 */
UCLASS()
class COPYCATSURVIVORS_API ACrazyCatCharacter : public ACopyCatSurvivorsCharacter
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintGetter)
	FColor GetLaserPointerColor() const  { return LaserPointerColor; }

	UFUNCTION(BlueprintGetter)
	float GetDashCoolDown() const  { return DashCooldown; }

	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	UFUNCTION(BlueprintPure)
	float GetHealthPercent() const { return CurrentHealth / InitialHealth; }

private:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=MechanicalProperties, meta=(AllowPrivateAccess = "true"))
	float MoveSpeed = 30.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=MechanicalProperties, meta=(AllowPrivateAccess = "true"))
	float InitialHealth = 30.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category=MechanicalProperties, meta=(AllowPrivateAccess = "true"))
	float CurrentHealth = 30.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category=MechanicalProperties, meta=(AllowPrivateAccess = "true"))
	float LaserPointerStrength = 30.f; //hur noggrant katterna ska följa den
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category=MechanicalProperties, meta=(AllowPrivateAccess = "true"))
	float DashCooldown = 3.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category=MechanicalProperties, meta=(AllowPrivateAccess = "true"))
	int ExtraLives = 3.f; //potentiellt också reduntadrt

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category=MechanicalProperties, meta=(AllowPrivateAccess = "true"))
	int NumberOfRerolls= 30.f; //uppgraderingar, när du har tillräckligt med bioamteria för uppdatering avv katt, reroll attt välja nya katter

	// skin på karaktär

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category=MechanicalProperties, meta=(AllowPrivateAccess = "true"))
	FColor LaserPointerColor = FColor::Red;

	void KillMe();

	// The Widget HUD class 
	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> HUDWidgetClass;

	// The actual Widget represented on screen, created in begin play 
	UPROPERTY()
	UUserWidget* HUDWidget; 
};
