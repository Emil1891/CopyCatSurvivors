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

private:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=MechanicalProperties, meta=(AllowPrivateAccess = "true"))
	float MoveSpeed = 30.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=MechanicalProperties, meta=(AllowPrivateAccess = "true"))
	float InitialHealth = 30.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category=MechanicalProperties, meta=(AllowPrivateAccess = "true"))
	float CurrentHealth = 30.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category=MechanicalProperties, meta=(AllowPrivateAccess = "true"))
	float LaserPointerStrength = 30.f;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category=MechanicalProperties, meta=(AllowPrivateAccess = "true"))
	float DashCooldown = 3.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category=MechanicalProperties, meta=(AllowPrivateAccess = "true"))
	int ExtraLives = 3.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category=MechanicalProperties, meta=(AllowPrivateAccess = "true"))
	int NumberOfRerolls= 30.f;

	// Outfit??

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category=MechanicalProperties, meta=(AllowPrivateAccess = "true"))
	FColor LaserPointerColor = FColor::Red;
	
};
