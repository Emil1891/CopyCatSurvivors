// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_FindLaser.h"

#include "AIController.h"
#include "CopyCatSurvivorsPlayerController.h"
#include "CrazyCatCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

UBTService_FindLaser::UBTService_FindLaser()
{
	NodeName = TEXT("Find laser pointer target location");
}

void UBTService_FindLaser::OnGameplayTaskActivated(UGameplayTask& Task)
{
	Super::OnGameplayTaskActivated(Task);
}

void UBTService_FindLaser::OnGameplayTaskDeactivated(UGameplayTask& Task)
{
	Super::OnGameplayTaskDeactivated(Task);
}

void UBTService_FindLaser::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	if(!PlayerPawn)
	{
		OwnerComp.GetBlackboardComponent()->ClearValue("LaserPointerTarget");
		return;
	}
	if (OwnerComp.GetAIOwner() == nullptr)
	{
		OwnerComp.GetBlackboardComponent()->ClearValue("LaserPointerTarget");
		return;
	}
	
	PlayerCharacter = Cast<ACrazyCatCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));
	if (!IsValid(PlayerCharacter) )
	{
		return;
	}
	ensure (PlayerCharacter != nullptr);
	
	if (PlayerCharacter->GetController())
	{
		ACopyCatSurvivorsPlayerController* OwnerController = Cast<ACopyCatSurvivorsPlayerController>(PlayerCharacter->GetController());
		if (OwnerController)
		{
			OwnerComp.GetBlackboardComponent()->SetValueAsVector("LaserPointerTarget", OwnerController->LaserPointerDestination);
		}
		
	}
	else
	{
		OwnerComp.GetBlackboardComponent()->ClearValue("LaserPointerTarget");

	}
	
}
