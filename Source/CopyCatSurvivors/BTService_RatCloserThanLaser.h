// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTService_RatCloserThanLaser.generated.h"

class ACat;
class ACrazyCatCharacter;
/**
 * 
 */
UCLASS()
class COPYCATSURVIVORS_API UBTService_RatCloserThanLaser : public UBTService_BlackboardBase
{
	GENERATED_BODY()

	
public: /** Constructor*/
	UBTService_RatCloserThanLaser();

	/** I have no idea when this is called but it is needed */
	virtual void OnGameplayTaskActivated(UGameplayTask& Task) override;

	/** I have no idea when this is called but it is needed as well */
	virtual void OnGameplayTaskDeactivated(UGameplayTask& Task) override;

	
protected:
	/** Tick node is called every tick service is in progress, checks if laser target location is further than rat that can be pounced*/
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

private:
	UPROPERTY()
	APawn* PlayerPawn;

	UPROPERTY()
	ACrazyCatCharacter* PlayerCharacter;

	float DistanceToRat = 0.f;
	float DistanceToLaserTarget = 0.f;

	UPROPERTY()
	ACat* OwnerCharacter;

	FVector OwnerCharacterLocation = FVector::ZeroVector;
};
