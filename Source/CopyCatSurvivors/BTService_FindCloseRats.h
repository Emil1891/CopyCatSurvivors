// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTService_FindCloseRats.generated.h"

class ACrazyCatCharacter;
/**
 * 
 */
UCLASS()
class COPYCATSURVIVORS_API UBTService_FindCloseRats : public UBTService_BlackboardBase
{
	GENERATED_BODY()

public: /** Constructor*/
	UBTService_FindCloseRats();

	/** I have no idea when this is called but it is needed */
	virtual void OnGameplayTaskActivated(UGameplayTask& Task) override;

	/** I have no idea when this is called but it is needed as well */
	virtual void OnGameplayTaskDeactivated(UGameplayTask& Task) override;

	UFUNCTION(BlueprintImplementableEvent)
	void OnCanPounceRatEvent();
	
protected:
	/** Tick node is called every tick service is in progress. Gets player character and sets blackboard value to laser point target in player controller*/
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

private:

	UPROPERTY()
	ACrazyCatCharacter* PlayerCharacter;

	/** Radius multiplier to multiply radius around character location to check for rats (multiplier for pounce distance in cat)*/
	UPROPERTY(EditAnywhere)
	float PounceDistanceMultiplier = 2.f;

	UPROPERTY(EditAnywhere)
	bool bDebug = false;
	
	
};
