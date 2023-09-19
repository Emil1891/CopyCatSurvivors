// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_FindLaser.h"

#include "CrazyCatCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

UBTService_FindLaser::UBTService_FindLaser()
{
	NodeName = TEXT("Find laser pointer target location");
}

void UBTService_FindLaser::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	if(!PlayerPawn)
	{
		OwnerComp.GetBlackboardComponent()->ClearValue("LaserPointerLocation");
		return;
	}
	
}
