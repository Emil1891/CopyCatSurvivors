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
	const FCollisionShape CheckSphereShape = FCollisionShape::MakeSphere(FindRatsRadius); //TODO: Radius should be OwnerCharacter->PounceDistance
	FCollisionObjectQueryParams Params = FCollisionObjectQueryParams();
	Params.AddObjectTypesToQuery(ECC_Pawn);
	TArray<FOverlapResult> OverlapResults;

	DrawDebugSphere(GetWorld(), MyLocation, FindRatsRadius, 24, FColor::Turquoise, false, .5f);

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
			// if overlap is found, set values in bb and remove laser point target location, and break (maybe, trying different things)
			if (RatCharacter && IsValid(RatCharacter))
			{
				OwnerComp.GetBlackboardComponent()->SetValueAsVector("ClosestRatLocation", RatCharacter->GetActorLocation());
				//tried having this service clear and set laser point target location, could be nice when balancing tree 
				
				DrawDebugSphere(GetWorld(), RatCharacter->GetActorLocation(), 30.f, 24, FColor::Green, false, .2f);

				OwnerComp.GetBlackboardComponent()->SetValueAsBool("bFoundRatsWithinPounceRadius", true);
			}
		}
		// KOD SOM CRASHADE MEN JAG ÄR FÖR TRÖTT
	}
	
	else
	{
		// if no overlaps found, clear values (and reset laser point target if we want)
		OwnerComp.GetBlackboardComponent()->ClearValue("ClosestRatLocation");
		OwnerComp.GetBlackboardComponent()->ClearValue("bFoundRatsWithinPounceRadius");
		
	}
}



/*  
		int IndexOfClosestRat = 0;
		float MinDistance = 1000000000.0f;
		for (int Index = 0; Index <= OverlapResults.Num(); Index++)
		{
			ARatCharacter* RatCharacter = Cast<ARatCharacter>(OverlapResults[Index].GetActor());

			DrawDebugSphere(GetWorld(), RatCharacter->GetActorLocation(), 30.f, 24, FColor::Green, false, .2f);

			// Calculate the distance between this character and rat
			float Distance = FVector::Distance(CatCharacter->GetActorLocation(), RatCharacter->GetActorLocation());

			// if overlap is found, check validity and set index of closest rat to the index of the rat
			if (RatCharacter && IsValid(RatCharacter))
			{
				if (Distance < MinDistance)
				{
					IndexOfClosestRat = Index;
					MinDistance = Distance;
				}
			}
		}
		

		// set values in bb and remove laser point target location, and break (maybe, trying different things)
		
		OwnerComp.GetBlackboardComponent()->SetValueAsVector("ClosestRatLocation", OverlapResults[IndexOfClosestRat].GetActor()->GetActorLocation());
		//tried having this service clear and set laser point target location, could be nice when balancing tree 
		//OwnerComp.GetBlackboardComponent()->ClearValue("LaserPointerTarget"); 
		OwnerComp.GetBlackboardComponent()->SetValueAsBool("bFoundRatsWithinPounceRadius", true);
		*/
	
	
