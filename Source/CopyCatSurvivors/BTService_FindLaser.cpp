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
		OwnerComp.GetBlackboardComponent()->ClearValue("LaserPointerLocation");
		GEngine->AddOnScreenDebugMessage(-1,200,FColor::Green,FString::Printf(TEXT("No player")));
		return;
	}
	if (OwnerComp.GetAIOwner() == nullptr)
	{
		OwnerComp.GetBlackboardComponent()->ClearValue("LaserPointerLocation");
		GEngine->AddOnScreenDebugMessage(-1,200,FColor::Green,FString::Printf(TEXT("No player controller")));

		return;
	}
		

	//ACrazyCatCharacter* PlayerCharacter = Cast<ACrazyCatCharacter>(OwnerComp.GetAIOwner()->GetCharacter());

	ACrazyCatCharacter* PlayerCharacter = Cast<ACrazyCatCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));
	if (!IsValid(PlayerCharacter) )
	{
		return;
	}
	ensure (PlayerCharacter != nullptr);

	
	if (PlayerCharacter->GetController())
	{
		GEngine->AddOnScreenDebugMessage(-1,200,FColor::Green,FString::Printf(TEXT("HAsController before cast")));

		ACopyCatSurvivorsPlayerController* OwnerController = Cast<ACopyCatSurvivorsPlayerController>(PlayerCharacter->GetController());
		if (OwnerController)
		{
			GEngine->AddOnScreenDebugMessage(-1,200,FColor::Green,FString::Printf(TEXT("HAsController from task")));
			OwnerComp.GetBlackboardComponent()->SetValueAsVector("LaserPointerLocation", OwnerController->LaserPointerDestination);
		}
		
	}
	else
	{
		OwnerComp.GetBlackboardComponent()->ClearValue("LaserPointerLocation");

	}
	
}
