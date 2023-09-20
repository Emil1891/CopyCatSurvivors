// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "XPDrop.generated.h"

UCLASS()
class COPYCATSURVIVORS_API AXPDrop : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AXPDrop();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	// The Xp drop mesh component 
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* MeshComp;

	UPROPERTY()
	class ACrazyCatCharacter* Player;

	UFUNCTION()
	void TriggerZoneHit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
							UPrimitiveComponent* OtherComponent, int OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY(EditAnywhere)
	int XPIncrease = 1; 
};
