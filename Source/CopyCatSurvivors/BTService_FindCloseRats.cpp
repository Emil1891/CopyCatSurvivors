// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_FindCloseRats.h"

#include "AIController.h"
#include "Cat.h"
#include "CopyCatSurvivorsPlayerController.h"
#include "CrazyCatCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "RatCharacter.h"
#include "Kismet/GameplayStatics.h"

UBTService_FindCloseRats::UBTService_FindCloseRats()
{
	NodeName = TEXT("Find close rats");
}

void UBTService_FindCloseRats::OnGameplayTaskActivated(UGameplayTask& Task)
{
	Super::OnGameplayTaskActivated(Task);
}

void UBTService_FindCloseRats::OnGameplayTaskDeactivated(UGameplayTask& Task)
{
	Super::OnGameplayTaskDeactivated(Task);
}

void UBTService_FindCloseRats::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	PlayerCharacter = Cast<ACrazyCatCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));
	if (!IsValid(PlayerCharacter) )
	{
		return;
	}
	ensure (PlayerCharacter != nullptr);

	
	if (OwnerComp.GetAIOwner() == nullptr) return;

	ACat* OwnerCharacter = Cast<ACat>(OwnerComp.GetAIOwner()->GetCharacter());

	if (OwnerCharacter == nullptr) return;

	// Make a sphere from cats location as large as defined radius
	const FVector MyLocation = OwnerCharacter->GetActorLocation();
	const FCollisionShape CheckSphereShape = FCollisionShape::MakeSphere(OwnerCharacter->PounceDistance * PounceDistanceMultiplier); 
	FCollisionObjectQueryParams Params = FCollisionObjectQueryParams();
	Params.AddObjectTypesToQuery(ECC_Pawn);
	TArray<FOverlapResult> OverlapResults;

	if (bDebug) DrawDebugSphere(GetWorld(), MyLocation, OwnerCharacter->PounceDistance  * PounceDistanceMultiplier, 24, FColor::Turquoise, false, .5f);

	// check if sphere overlaps with any rats
	bool bOverlaps = GetWorld()->OverlapMultiByObjectType(
		OverlapResults,
		MyLocation,
		FQuat::Identity,
		Params,
		CheckSphereShape);
	
	if(bOverlaps)
	{
		for(FOverlapResult Overlap : OverlapResults)
		{
			ARatCharacter* RatCharacter = Cast<ARatCharacter>(Overlap.GetActor());
			// if overlap is found, set values in bb
			if (RatCharacter && IsValid(RatCharacter))
			{
				OwnerComp.GetBlackboardComponent()->SetValueAsVector("PounceRatLocation", RatCharacter->GetActorLocation());
				//tried having this service clear and set laser point target location, could be nice when balancing tree
				OwnerComp.GetBlackboardComponent()->SetValueAsBool("bFoundRatsWithinPounceRadius", true);
				OnCanPounceRatEvent();
				
				if (bDebug)	DrawDebugSphere(GetWorld(), RatCharacter->GetActorLocation(), 30.f, 24, FColor::Green, false, .2f);
			}
		}
	}
	
	else
	{
		// if no overlaps found, clear values (and reset laser point target if we want)
		OwnerComp.GetBlackboardComponent()->ClearValue("PounceRatLocation");
		OwnerComp.GetBlackboardComponent()->SetValueAsBool("bFoundRatsWithinPounceRadius", false);

		OwnerComp.GetBlackboardComponent()->ClearValue("bFoundRatsWithinPounceRadius");
		
	}
}

