// Copyright Epic Games, Inc. All Rights Reserved.

#include "CopyCatSurvivorsPlayerController.h"
#include "GameFramework/Pawn.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"
#include "CopyCatSurvivorsCharacter.h"
#include "CrazyCatCharacter.h"
#include "Engine/World.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/PawnMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

ACopyCatSurvivorsPlayerController::ACopyCatSurvivorsPlayerController()
{
	DefaultMouseCursor = EMouseCursor::Default;
	LaserPointerDestination = FVector::ZeroVector;
}

void ACopyCatSurvivorsPlayerController::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	//Add Input Mapping Context
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
	}

	PlayerCharacter = Cast<ACrazyCatCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (PlayerCharacter)
	{
		LaserPointerColor = PlayerCharacter->GetLaserPointerColor();
		DashCooldownDuration = PlayerCharacter->GetDashCoolDown();
	}
}

void ACopyCatSurvivorsPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	DoLaserPointer();
    
}


void ACopyCatSurvivorsPlayerController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();

	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent))
	{
		// Setup mouse input events
		EnhancedInputComponent->BindAction(MoveCatForwardAction, ETriggerEvent::Triggered, this, &ACopyCatSurvivorsPlayerController::MoveCatForward);
		EnhancedInputComponent->BindAction(MoveCatRightAction, ETriggerEvent::Triggered, this, &ACopyCatSurvivorsPlayerController::MoveCatRight);
		EnhancedInputComponent->BindAction(DashCatAction, ETriggerEvent::Triggered, this, &ACopyCatSurvivorsPlayerController::DashCat);

	}
}


void ACopyCatSurvivorsPlayerController::MoveCatForward(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	// Get look direction
	FRotator MoveRotation(GetControlRotation().Pitch, GetControlRotation().Yaw, 0.0f);

	APawn* ControlledPawn = GetPawn();
	if (ControlledPawn != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = MoveRotation.RotateVector(FVector::ForwardVector);
		
		// add movement 
		ControlledPawn->AddMovementInput(ForwardDirection, MovementVector.X);
	}
}

void ACopyCatSurvivorsPlayerController::MoveCatRight(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	// Get look direction
	FRotator MoveRotation(GetControlRotation().Pitch, GetControlRotation().Yaw, 0.0f);

	APawn* ControlledPawn = GetPawn();
	if (ControlledPawn != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector RightDirection = MoveRotation.RotateVector(FVector::RightVector);
		
		// add movement 
		ControlledPawn->AddMovementInput(RightDirection, MovementVector.X);
	}
}

void ACopyCatSurvivorsPlayerController::DashCat()
{
	OnDashInput();
}

void ACopyCatSurvivorsPlayerController::DoLaserPointer()
{
	
	FHitResult Hit;
	
	bool bHitSuccessful = GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, true, Hit);
	
	if (bHitSuccessful)
	{
		LaserPointerDestination = Hit.Location;
	}

	DrawDebugSphere(GetWorld(), LaserPointerDestination, 10.f, 30, LaserPointerColor, false, 0.1, 0, 1);
	DrawDebugLine(GetWorld(), GetPawn()->GetActorLocation(), LaserPointerDestination, LaserPointerColor, false, 0.1, 0, 1);
}


void ACopyCatSurvivorsPlayerController::Dash()
{
	GetCharacter()->LaunchCharacter(
		GetPawn()->GetActorForwardVector() * DashStrength,
		false,
		false
		);
}
