// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTService_FindLaser.generated.h"

class ACrazyCatCharacter;
/**
 * 
 */
UCLASS()
class COPYCATSURVIVORS_API UBTService_FindLaser : public UBTService_BlackboardBase
{
	GENERATED_BODY()
public:
	/** Constructor*/
	UBTService_FindLaser();

	/** I have no idea when this is called but it is needed */
	virtual void OnGameplayTaskActivated(UGameplayTask& Task) override;

	/** I have no idea when this is called but it is needed as well */
	virtual void OnGameplayTaskDeactivated(UGameplayTask& Task) override;
	
protected:
	/** Tick node is called every tick service is in progress. Gets player character and sets blackboard value to laser point target in player controller*/
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	
private:
	/** Pointer to player pawn*/
	UPROPERTY()
	APawn* PlayerPawn;

	/** Pointer to player character*/
	UPROPERTY()
	ACrazyCatCharacter* PlayerCharacter;
	

};
