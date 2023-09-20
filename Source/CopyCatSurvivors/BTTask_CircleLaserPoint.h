// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_CircleLaserPoint.generated.h"

/**
 * 
 */
UCLASS()
class COPYCATSURVIVORS_API UBTTask_CircleLaserPoint : public UBTTask_BlackboardBase
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
	UBTTask_CircleLaserPoint();

private:

	/** Point to move around*/
	FVector CenterPoint = FVector::ZeroVector;

	/** Radius of circle to move around*/
	UPROPERTY(EditAnywhere)
	float CircleRadius = 100.0f;

	UPROPERTY(EditAnywhere)
	float MoveSpeed = 100.0f;

	UPROPERTY(EditAnywhere)
	float CurrentAngle;
};
