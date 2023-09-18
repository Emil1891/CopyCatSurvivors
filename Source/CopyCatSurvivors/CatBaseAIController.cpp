// Fill out your copyright notice in the Description page of Project Settings.


#include "CatBaseAIController.h"

#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

void ACatBaseAIController::Initialize()
{
	// choose bt to run
	if(BehaviorTree)
	{
		RunBehaviorTree(BehaviorTree);
	}
	UE_LOG(LogTemp, Warning, TEXT("BehaviourTReetorun %s"), *BehaviorTree->GetName());
	//GetBlackboardComponent()->SetValueAsVector(TEXT("StartLocation"), this->GetPawn()->());
	
}

void ACatBaseAIController::BeginPlay()
{
	Super::BeginPlay();
}
