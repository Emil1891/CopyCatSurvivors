// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class COPYCATSURVIVORS_API GridNode
{
public:
	GridNode(const bool bIsWalkable, const FVector WorldCoord, const int GridX, const int GridY);
	GridNode() {}

	// Sets its direction based on passed TargetNode (Node which this node should points towards)
	void SetDirection(const GridNode* TargetNode); 

	FVector GetDirection() const { return Direction; }

	bool IsWalkable() const { return bWalkable; }

	FVector GetWorldCoordinate() const { return WorldCoordinate; }

	int GetCost() const { return Cost; }

	void SetCost(const int NewCost) { Cost = NewCost; }

	int GridX = -1;
	int GridY = -1; 

private:
	// Direction where the AI should walk if standing on this node 
	FVector Direction = FVector::Zero();

	// If the node is walkable 
	bool bWalkable = false;

	FVector WorldCoordinate;

	// Cost to get to this node 
	int Cost = INT_MAX; 
};
