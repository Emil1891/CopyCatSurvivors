// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_FindCloseRats.h"

#include "AIController.h"
#include "Cat.h"
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

	// Make a sphere trace from where cat is to detect enemy rats
	if (OwnerComp.GetAIOwner() == nullptr) return;

	ACat* CatCharacter = Cast<ACat>(OwnerComp.GetAIOwner()->GetCharacter());

	if (CatCharacter == nullptr) return;

	const FVector MyLocation = CatCharacter->GetActorLocation();
	const FVector MidwayPoint = MyLocation + (MyLocation  - FindRatsRadius) / 2;
	const FCollisionShape CheckSphereShape = FCollisionShape::MakeSphere(FindRatsRadius); //TODO: Detta borde vara en distance som sätts i katten, alternativt en radius i bb
	FCollisionObjectQueryParams Params = FCollisionObjectQueryParams();
	Params.AddObjectTypesToQuery(ECC_GameTraceChannel8);
	TArray<FOverlapResult> OverlapResults;

	DrawDebugSphere(GetWorld(), MidwayPoint, FindRatsRadius, 24, FColor::Turquoise, false, .5f);
	
	bool bOverlaps = GetWorld()->OverlapMultiByObjectType(
		OverlapResults,
		MidwayPoint,
		FQuat::Identity,
		Params,
		CheckSphereShape);
	if(bOverlaps)
	{
		for(FOverlapResult Overlap : OverlapResults)
		{
			ARatCharacter* RatCharacter = Cast<ARatCharacter>(Overlap.GetActor());
			if (RatCharacter && IsValid(RatCharacter))
			{
				OwnerComp.GetBlackboardComponent()->SetValueAsVector("ClosestRatLocation", RatCharacter->GetActorLocation());
				
				OwnerComp.GetBlackboardComponent()->SetValueAsBool("bFoundRatsWithinPounceRadius", true);
				break;
				//TODO: Sätta en bool i bb som säger att vi hittat råttor och en rått-location. Sen - I Pounce task - gör en sfär runt råttan och launch character mot den sålänge cooldown tillåter det
				//TODO: När cat är nära target point och inget annat händer - spring i cirklar.
				// TODO: Om cat är ännu närmare rat så ska den gå in i en sekvens av bite + claw.
			}
		}
	}
	else
	{
		OwnerComp.GetBlackboardComponent()->ClearValue("ClosestRatLocation");
		OwnerComp.GetBlackboardComponent()->SetValueAsBool("bFoundRatsWithinPounceRadius", false);
	}
}

