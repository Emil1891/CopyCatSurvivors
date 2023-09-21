// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Claw.h"

#include "AIController.h"
#include "Cat.h"
#include "RatCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"


UBTTask_Claw::UBTTask_Claw()
{
	NodeName = TEXT("Claw");
}

void UBTTask_Claw::OnGameplayTaskActivated(UGameplayTask& Task)
{
	Super::OnGameplayTaskActivated(Task);

	
}

EBTNodeResult::Type UBTTask_Claw::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);
	
	// code below makes it so TickTask is called 
	bNotifyTick = 1;
	return EBTNodeResult::InProgress; 
}

void UBTTask_Claw::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	// Cache the cat character's start location
	OwnerCharacter = Cast<ACat>(OwnerComp.GetAIOwner()->GetPawn());
	if (OwnerCharacter)
	{
		OwnerLocation = OwnerCharacter->GetActorLocation();
	}

	ARatCharacter* RatCharacter = nullptr;
	UObject* RatObject = OwnerComp.GetAIOwner()->GetBlackboardComponent()->GetValueAsObject("RatToClaw");
	if (RatObject)
	{
		RatCharacter = Cast<ARatCharacter>(RatObject);
	}
	if (RatCharacter && IsValid(RatCharacter))
	{
		OnClawAttack();
		OwnerCharacter->OnClawAttack();
		UGameplayStatics::ApplyDamage(RatCharacter, OwnerCharacter->ClawDamage, OwnerCharacter->GetController(), OwnerCharacter, nullptr);
	}

	OwnerComp.GetBlackboardComponent()->ClearValue("RatToClaw");
	OwnerComp.GetBlackboardComponent()->SetValueAsBool("bFoundRatsWithinClawRadius", false);
}
