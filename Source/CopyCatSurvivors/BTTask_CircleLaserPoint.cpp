// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_CircleLaserPoint.h"

#include "AIController.h"
#include "CrazyCatCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_CircleLaserPoint::UBTTask_CircleLaserPoint()
{
	NodeName = TEXT("CircleLaserPoint");
}

void UBTTask_CircleLaserPoint::OnGameplayTaskActivated(UGameplayTask& Task)
{
	Super::OnGameplayTaskActivated(Task);
}

EBTNodeResult::Type UBTTask_CircleLaserPoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	// Get cat and blackboard comp
	ACrazyCatCharacter* OwnerCharacter = Cast<ACrazyCatCharacter>(OwnerComp.GetAIOwner()->GetPawn());
	UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();

	if (OwnerCharacter && BlackboardComp)
	{
		// Get the center point from the blackboard
		CenterPoint = BlackboardComp->GetValueAsVector("LaserPointerTarget");

		// Calculate the initial angle for circular movement
		CurrentAngle = FMath::RandRange(0.0f, 360.0f);

		// code below makes it so TickTask is called 
		bNotifyTick = 1;
		return EBTNodeResult::InProgress; 
	}
	return EBTNodeResult::Failed;	
}

void UBTTask_CircleLaserPoint::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	// Check if cat is moving in circle
	if (MoveSpeed > 0.0f)
	{
		// Calculate the new angle for circular movement
		float DeltaAngle = DeltaSeconds * MoveSpeed; // eller kanske -DeltaSeconds * MoveSpeed;
		CurrentAngle += DeltaAngle;

		// Calculate the new location 
		FVector NewLocation = CenterPoint + FVector(FMath::Cos(FMath::DegreesToRadians(CurrentAngle)), FMath::Sin(FMath::DegreesToRadians(CurrentAngle)), 0) * CircleRadius;

		// Move cat to location
		ACharacter* OwnerCharacter = Cast<ACharacter>(OwnerComp.GetAIOwner()->GetPawn());
		if (OwnerCharacter)
		{
			OwnerCharacter->SetActorLocation(NewLocation);
		}
	}
}


