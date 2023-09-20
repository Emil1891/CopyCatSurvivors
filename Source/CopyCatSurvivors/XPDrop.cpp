// Fill out your copyright notice in the Description page of Project Settings.


#include "XPDrop.h"

#include "CrazyCatCharacter.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AXPDrop::AXPDrop()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	MeshComp->SetupAttachment(RootComponent);

	// Bind function to call when overlap starts 
	MeshComp->OnComponentBeginOverlap.AddDynamic(this, &AXPDrop::TriggerZoneHit);

}

// Called when the game starts or when spawned
void AXPDrop::BeginPlay()
{
	Super::BeginPlay();

	Player = Cast<ACrazyCatCharacter>(UGameplayStatics::GetPlayerPawn(this, 0)); 
}

void AXPDrop::TriggerZoneHit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComponent, int OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(OtherActor != Player)
		return;

	Player->IncreaseXP(XPIncrease);

	Destroy(); 
}

