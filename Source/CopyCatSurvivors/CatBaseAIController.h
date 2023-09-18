// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "CatBaseAIController.generated.h"

/**
 * 
 */
UCLASS()
class COPYCATSURVIVORS_API ACatBaseAIController : public AAIController
{
	GENERATED_BODY()

public:
	/** Chooses which behaviour tree to run, and if tree not null runs it and sets blackboard values */
	void Initialize();

	virtual void BeginPlay() override;

	/** Behavior tree to control behavior */
	UPROPERTY(EditAnywhere)
	UBehaviorTree* BehaviorTree;
	
};
