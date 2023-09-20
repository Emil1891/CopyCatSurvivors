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

	ACat* CatCharacter = Cast<ACat>(OwnerComp.GetAIOwner()->GetCharacter());

	if (CatCharacter == nullptr) return;

	// Make a sphere from cats location as large as defined radius
	const FVector MyLocation = CatCharacter->GetActorLocation();
	//const FVector MidwayPoint = MyLocation + MyLocation.ForwardVector * FindRatsRadius;
	const FCollisionShape CheckSphereShape = FCollisionShape::MakeSphere(FindRatsRadius); //TODO: Detta borde vara en distance som sätts i katten, alternativt en radius i bb
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
				OwnerComp.GetBlackboardComponent()->ClearValue("LaserPointerTarget");

				DrawDebugSphere(GetWorld(), RatCharacter->GetActorLocation(), 30.f, 24, FColor::Green, false, .2f);

				OwnerComp.GetBlackboardComponent()->SetValueAsBool("bFoundRatsWithinPounceRadius", true);
				//break;
			}
		}
	}
	else
	{
		// if no overlaps found, clear values and reset laser point target
		OwnerComp.GetBlackboardComponent()->ClearValue("ClosestRatLocation");
		OwnerComp.GetBlackboardComponent()->ClearValue("bFoundRatsWithinPounceRadius");
		if (PlayerCharacter->GetController())
		{
			ACopyCatSurvivorsPlayerController* OwnerController = Cast<ACopyCatSurvivorsPlayerController>(PlayerCharacter->GetController());
			if (OwnerController)
			{
				OwnerComp.GetBlackboardComponent()->SetValueAsVector("LaserPointerTarget", OwnerController->LaserPointerDestination);
			}
		}
	}
}

