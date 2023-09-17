// Fill out your copyright notice in the Description page of Project Settings.


#include "Pathfinder.h"

#include "MapGrid.h"

Pathfinder::Pathfinder(APawn* PlayerActor, AMapGrid* MapGrid) : Player(PlayerActor), Grid(MapGrid)
{
}

void Pathfinder::UpdateNodeDirections()
{
	const FVector PlayerPos = Player->GetActorLocation();
	
	if(PlayerPos.Equals(OldPlayerLocation))
		return;

	GridNode* TargetNode = Grid->GetNodeFromWorldLocation(PlayerPos);
	TargetNode->SetCost(0);

	
}

Pathfinder::~Pathfinder()
{
}
