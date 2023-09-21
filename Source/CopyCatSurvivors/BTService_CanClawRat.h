// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTService_CanClawRat.generated.h"

class ACat;
/**
 * 
 */
UCLASS()
class COPYCATSURVIVORS_API UBTService_CanClawRat : public UBTService_BlackboardBase
{
	GENERATED_BODY()

	
public: /** Constructor*/
	UBTService_CanClawRat();

	/** I have no idea when this is called but it is needed */
	virtual void OnGameplayTaskActivated(UGameplayTask& Task) override;

	/** I have no idea when this is called but it is needed as well */
	virtual void OnGameplayTaskDeactivated(UGameplayTask& Task) override;

	UFUNCTION(BlueprintImplementableEvent)
	void OnCanClawRatEvent();
	
protected:
	/** Tick node is called every tick service is in progress*/
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	UPROPERTY()
	ACat* OwnerCharacter;

	UPROPERTY(EditAnywhere)
	bool bDebug = false;

	UPROPERTY(EditAnywhere)
	float ClawDistance = 50.f;

	
};
