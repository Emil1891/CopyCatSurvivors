// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Pounce.h"

#include "AIController.h"
#include "Cat.h"
#include "CrazyCatCharacter.h"
#include "RatCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Engine/DamageEvents.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"


UBTTask_Pounce::UBTTask_Pounce()
{
	NodeName = TEXT("Pounce");
	bPouncing = false;
}


void UBTTask_Pounce::OnGameplayTaskActivated(UGameplayTask& Task)
{
	Super::OnGameplayTaskActivated(Task);
}

EBTNodeResult::Type UBTTask_Pounce::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);
	
	// Set the cooldown timer and indicate that the cat is currently pouncing
	if (!bPouncing)
	{
		PounceCooldownTimer = PounceCooldownTime;
		bPouncing = true;
	}
	
	// code below makes it so TickTask is called 
	bNotifyTick = 1;
	return EBTNodeResult::InProgress; 
}

void UBTTask_Pounce::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	
	// Cache the cat character's start location
	OwnerCharacter = Cast<ACat>(OwnerComp.GetAIOwner()->GetPawn());
	if (OwnerCharacter)
	{
		StartLocation = OwnerCharacter->GetActorLocation();
	}

	// Check if value is set - cache the target location (TargetLocation)
	if (OwnerComp.GetBlackboardComponent()->IsVectorValueSet("PounceRatLocation"))
	{
		TargetLocation = OwnerComp.GetBlackboardComponent()->GetValueAsVector("PounceRatLocation");
	}
	
	// If cat is currently pouncing
	if (bPouncing)
	{
		// if the cooldown timer has expired
		if (PounceCooldownTimer <= 0.0f)
		{
			// Launch cat towards the target location.
			if (OwnerCharacter)
			{
				FVector LaunchDirection = (TargetLocation  - StartLocation).GetSafeNormal();
				FVector LaunchVelocity = LaunchDirection * PounceForce; 
				OwnerCharacter->LaunchCharacter(LaunchVelocity, true, true);
				OnPounceAttack();
				if (bDebug)GEngine->AddOnScreenDebugMessage(-1,2,FColor::Green,FString::Printf(TEXT("launching character for pouncing")));

				//GetWorld()->GetTimerManager().SetTimer(RetreatTimerHandle, this, &UBTTask_Pounce::MoveCharacterBack, 0.1f, false, RetreatDelay);
				MakePounceAreaDamage();
			}

			// Reset pounce flag and reset the cooldown timer for the next pounce
			PounceCooldownTimer = PounceCooldownTime;
		}
		else
		{
			// Decrease the cooldown timer
			PounceCooldownTimer -= DeltaSeconds;
		}
	}
	else
	{
		// If not pouncing, move the character back to the start location
		if (OwnerCharacter)
		{
			FVector MoveDirection = (StartLocation - OwnerCharacter->GetActorLocation()).GetSafeNormal();
			// should be replaced with characters move speed
			FVector MoveVelocity = MoveDirection * ReturnSpeed;
			OwnerCharacter->AddMovementInput(MoveVelocity , 1.0f);

			// Check if cat has reached the start location to start the next pounce
			float DistanceToStart = FVector::Distance(OwnerCharacter->GetActorLocation(), StartLocation);
			if (DistanceToStart < 10.0f) 
			{
				bPouncing = true;
			}
		}
	}
	GetWorld()->GetTimerManager().ClearTimer(RetreatTimerHandle);
}

void UBTTask_Pounce::MakePounceAreaDamage()
{
	// Make a sphere from cats location as large as defined radius
	const FVector CenterLocation = TargetLocation;
	const FCollisionShape CheckSphereShape = FCollisionShape::MakeSphere(PounceDamageRadius); 
	FCollisionObjectQueryParams Params = FCollisionObjectQueryParams();
	Params.AddObjectTypesToQuery(ECC_Pawn);
	TArray<FOverlapResult> OverlapResults;

	if (bDebug) DrawDebugSphere(GetWorld(), CenterLocation, PounceDamageRadius, 24, FColor::Red, false, .5f);

	// check if sphere overlaps with any rats
	bool bOverlaps = GetWorld()->OverlapMultiByObjectType(
		OverlapResults,
		CenterLocation,
		FQuat::Identity,
		Params,
		CheckSphereShape);
	
	if(bOverlaps)
	{
		for(FOverlapResult Overlap : OverlapResults)
		{
			ARatCharacter* RatCharacter = Cast<ARatCharacter>(Overlap.GetActor());
			// if overlap is found, do damage
			if (RatCharacter && IsValid(RatCharacter))
			{
				if (bDebug)DrawDebugSphere(GetWorld(), RatCharacter->GetActorLocation(), 30.f, 24, FColor::Orange, false, .2f);
				if (bDebug)GEngine->AddOnScreenDebugMessage(-1,200,FColor::Green,FString::Printf(TEXT("Pouncing ")));

				// maybe apply force/launch the rats?
				UGameplayStatics::ApplyDamage(RatCharacter, OwnerCharacter->PounceDamage, OwnerCharacter->GetController(), OwnerCharacter,nullptr);
			}
		}
	}
}

void UBTTask_Pounce::MoveCharacterBack()
{
	UE_LOG(LogTemp, Warning, TEXT("REtreating"));
	FVector LaunchDirection = (StartLocation - TargetLocation).GetSafeNormal();
	FVector LaunchVelocity = LaunchDirection * PounceForce;
	OwnerCharacter->LaunchCharacter(LaunchVelocity, true, true);
}




