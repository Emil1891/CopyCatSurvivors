// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

class AMapGrid;
/**
 * 
 */
class COPYCATSURVIVORS_API Pathfinder
{
public:
	Pathfinder(APawn* PlayerActor, AMapGrid* MapGrid);

	// Called each tick from MapGrid 
	void UpdateNodeDirections();

private:
	APawn* Player;

	// Makes it possible to skip pathfinding if player has not moved 
	FVector OldPlayerLocation = FVector::Zero();

	AMapGrid* Grid;

	// Sets cost to int_max for each node 
	void ResetNodeCosts(); 
};
