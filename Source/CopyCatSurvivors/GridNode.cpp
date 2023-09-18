// Fill out your copyright notice in the Description page of Project Settings.

#include "GridNode.h"

GridNode::GridNode(const bool bIsWalkable, const FVector WorldCoord, const int GridX, const int GridY) :
	GridX(GridX), GridY(GridY),  bWalkable(bIsWalkable), WorldCoordinate(WorldCoord)
{
}

void GridNode::SetDirection(const GridNode* TargetNode)
{
	Direction = TargetNode->WorldCoordinate - WorldCoordinate;
	Direction.Normalize();
}
