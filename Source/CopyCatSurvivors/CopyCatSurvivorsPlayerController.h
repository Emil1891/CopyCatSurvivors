 // Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Templates/SubclassOf.h"
#include "GameFramework/PlayerController.h"
#include "InputActionValue.h"
#include "CopyCatSurvivorsPlayerController.generated.h"

 class ACrazyCatCharacter;
/** Forward declaration to improve compiling times */
class UNiagaraSystem;

UCLASS()
class ACopyCatSurvivorsPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ACopyCatSurvivorsPlayerController();

	/** Time Threshold to know if it was a short press */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	float ShortPressThreshold;

	/** FX Class that we will spawn when clicking */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UNiagaraSystem* FXCursor;

	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputMappingContext* DefaultMappingContext;
	
	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputAction* SetDestinationClickAction;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputAction* SetDestinationTouchAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* MoveCatForwardAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* MoveCatRightAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* DashCatAction;

	/** Destination that is target for cat army*/
	FVector LaserPointerDestination;

	/** On dash input event*/
	UFUNCTION(BlueprintImplementableEvent)
	void OnDashInput();

	/** Bool to enable laser pointer*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bDoLaser = true;
	
protected:
	

	virtual void SetupInputComponent() override;
	
	// To add mapping context
	virtual void BeginPlay();

	virtual void Tick(float DeltaSeconds) override;

	void MoveCatForward(const FInputActionValue& Value);
	void MoveCatRight(const FInputActionValue& Value);
	void DashCat();

	void DoLaserPointer();

private:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category=Player, meta=(AllowPrivateAccess = "true"))
	ACrazyCatCharacter* PlayerCharacter = nullptr;

	// ======== Dash variables and methods ======/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	float DashStrength = 5.f;
	
	UFUNCTION(BlueprintCallable)
	void Dash();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Dash, meta=(AllowPrivateAccess = "true"))
	float DashCooldownDuration = 0.0f;
    
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Dash, meta=(AllowPrivateAccess = "true"))
	FColor LaserPointerColor = FColor::Green;
};




