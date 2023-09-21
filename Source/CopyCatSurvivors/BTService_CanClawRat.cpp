// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_CanClawRat.h"

#include "AIController.h"
#include "Cat.h"
#include "RatCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTService_CanClawRat::UBTService_CanClawRat()
{
	NodeName = TEXT("CanClawRat");
}

void UBTService_CanClawRat::OnGameplayTaskActivated(UGameplayTask& Task)
{
	Super::OnGameplayTaskActivated(Task);
}

void UBTService_CanClawRat::OnGameplayTaskDeactivated(UGameplayTask& Task)
{
	Super::OnGameplayTaskDeactivated(Task);
}

void UBTService_CanClawRat::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	if (OwnerComp.GetAIOwner() == nullptr) return;

	OwnerCharacter = Cast<ACat>(OwnerComp.GetAIOwner()->GetCharacter());

	if (OwnerCharacter == nullptr) return;

	// Make a sphere from cats location as large as defined radius
	const FVector MyLocation = OwnerCharacter->GetActorLocation();
	const FCollisionShape CheckSphereShape = FCollisionShape::MakeSphere(ClawDistance); 
	FCollisionObjectQueryParams Params = FCollisionObjectQueryParams();
	Params.AddObjectTypesToQuery(ECC_Pawn);
	TArray<FOverlapResult> OverlapResults;

	if (bDebug) DrawDebugSphere(GetWorld(), MyLocation, ClawDistance, 24, FColor::Black, false, .5f);

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
			// if overlap is found, set values in bb and break
			if (RatCharacter && IsValid(RatCharacter))
			{
				OnCanClawRatEvent();
				OwnerComp.GetBlackboardComponent()->SetValueAsObject("RatToClaw", RatCharacter);
				
				if (bDebug)	DrawDebugSphere(GetWorld(), RatCharacter->GetActorLocation(), 30.f, 24, FColor::Blue, false, .2f);
				
				OwnerComp.GetBlackboardComponent()->SetValueAsBool("bFoundRatsWithinClawRadius", true);
				break;

			}
		}
	}
}
