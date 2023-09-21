// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_RatCloserThanLaser.h"

#include "AIController.h"
#include "Cat.h"
#include "CopyCatSurvivorsPlayerController.h"
#include "CrazyCatCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

UBTService_RatCloserThanLaser::UBTService_RatCloserThanLaser()
{
	NodeName = TEXT("IsRatCloserThanLaser");
}

void UBTService_RatCloserThanLaser::OnGameplayTaskActivated(UGameplayTask& Task)
{
	Super::OnGameplayTaskActivated(Task);
}

void UBTService_RatCloserThanLaser::OnGameplayTaskDeactivated(UGameplayTask& Task)
{
	Super::OnGameplayTaskDeactivated(Task);
}

void UBTService_RatCloserThanLaser::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
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

			OwnerCharacter = Cast<ACat>(OwnerComp.GetAIOwner()->GetCharacter());

			if (OwnerCharacter == nullptr) return;

			OwnerCharacterLocation = OwnerCharacter->GetActorLocation();
			
			DistanceToLaserTarget = FVector::Distance(OwnerCharacterLocation, OwnerComp.GetBlackboardComponent()->GetValueAsVector("LaserPointerTarget"));
			DistanceToRat = FVector::Distance(OwnerCharacterLocation, OwnerComp.GetBlackboardComponent()->GetValueAsVector("PounceRatLocation"));

			OwnerComp.GetBlackboardComponent()->SetValueAsBool("bIsRatCloserThanLaserTarget", DistanceToRat < DistanceToLaserTarget);
		}
	}
}
