// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTService_FindLaser.generated.h"

/**
 * 
 */
UCLASS()
class COPYCATSURVIVORS_API UBTService_FindLaser : public UBTService_BlackboardBase
{
	GENERATED_BODY()
public:
	UBTService_FindLaser();
	
protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	
private:
	UPROPERTY()
	APawn* PlayerPawn;
	
};
