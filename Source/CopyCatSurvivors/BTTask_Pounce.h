// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_Pounce.generated.h"

/**
 * 
 */
UCLASS()
class COPYCATSURVIVORS_API UBTTask_Pounce : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
	/** I have no idea when this is called but it is needed */
	virtual void OnGameplayTaskActivated(UGameplayTask& Task) override;

	/** Execute task is called once every time this task is activated */
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	/** Tick task is called every tick this task is in progress, set up in execute task */
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	/** Constructor*/
	UBTTask_Pounce();
private:

	/** Force to launch character toward target*/
	UPROPERTY(EditAnywhere)
	float PounceForce = 40.f;

	/** Pounce cooldown, deciding how often character performs the pounce*/
	UPROPERTY(EditAnywhere)
	float PounceCooldownTime = 5.f;

	/** Timer to check cool down*/
	float PounceCooldownTimer = 0.0f;

	/** Speed when returning to start position*/
	UPROPERTY(EditAnywhere)
	float ReturnSpeed = 30.f;

	// array of rats? choose a rat and attack. Maybe rats should have a bool if an instance is targeted?
	/** Rat location*/
	FVector TargetLocation;

	/** Initial location from where to start pouncing attack from*/
	FVector StartLocation;

	/** Is true when cat is performing the pouncing attack*/	
	bool bPouncing;
	
};
