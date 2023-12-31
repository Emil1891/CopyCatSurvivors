// Fill out your copyright notice in the Description page of Project Settings.

#include "BTTask_MoveTowardsPlayer.h"

#include "AIController.h"
#include "MapGrid.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Engine/DamageEvents.h"
#include "Kismet/GameplayStatics.h"

void UBTTask_MoveTowardsPlayer::OnGameplayTaskActivated(UGameplayTask& Task)
{
	Super::OnGameplayTaskActivated(Task);
}

EBTNodeResult::Type UBTTask_MoveTowardsPlayer::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	// Assign Grid if not already assigned 
	if(!Grid)
		Grid = Cast<AMapGrid>(UGameplayStatics::GetActorOfClass(this, AMapGrid::StaticClass()));

	// Assign Player if not already assigned
	if(!Player)
		Player = UGameplayStatics::GetPlayerPawn(this, 0); 
	
	// code below makes it so TickTask is called 
	bNotifyTick = 1;
	return EBTNodeResult::InProgress; 
}

void UBTTask_MoveTowardsPlayer::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	// Apparently needs to be found/set each tick because storing it as a data member means each AI shares it :/ 
	APawn* Owner = OwnerComp.GetAIOwner()->GetPawn();
	
	const FVector OwnerLoc = Owner->GetActorLocation(); 
	
	// If AI has reached its target, finish task as a success 
	if(Player->GetActorLocation().Equals(OwnerLoc, SuccessRange))
	{
		// Owner->TakeDamage(3, FDamageEvent(), Owner->GetController(), Owner); // only used to test stuff 
		return FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
	
	// Otherwise move towards player
	const FVector MoveDir = Grid->GetDirectionBasedOnWorldLocation(OwnerLoc);
	const FVector NewLocDelta = MoveDir * MoveSpeed * DeltaSeconds;
	Owner->SetActorLocation(OwnerLoc + NewLocDelta);
	
	// flip sprite if walking "backwards" (NOTE THIS ASSUMES A SCALE OF ONE IS USED)
	if(MoveDir.Y < 0)
		Owner->SetActorScale3D(FVector(1, -1, 1)); 
	else
		Owner->SetActorScale3D(FVector::One());

	return FinishLatentTask(OwnerComp, EBTNodeResult::InProgress);
}
