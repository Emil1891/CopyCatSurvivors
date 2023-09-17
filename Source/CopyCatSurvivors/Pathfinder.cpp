// Fill out your copyright notice in the Description page of Project Settings.

#include "Pathfinder.h"

#include "MapGrid.h"

namespace // helper functions 
{
	// returns false/true whether or not moving from currentNode to nextNode would be a diagonal move 
	bool IsMovingDiagonally(const GridNode* Current, const GridNode* NextNode)
	{
		// if either x or y coordinate is the same for both nodes, then seeker is not moving diagonally and vice versa 
		return !(Current->GridX == NextNode->GridX || Current->GridY == NextNode->GridY); 
	}

	int CostToNode(const GridNode* Current, const GridNode* NextNode)
	{
		return IsMovingDiagonally(Current, NextNode) ? 14 : 10; 
	}
}

Pathfinder::Pathfinder(APawn* PlayerActor, AMapGrid* MapGrid) : Player(PlayerActor), Grid(MapGrid)
{
}

// Some inspiration from https://leifnode.com/2013/12/flow-field-pathfinding/ 
void Pathfinder::UpdateNodeDirections()
{
	const FVector PlayerPos = Player->GetActorLocation();

	// If player has not moved, no need yo update the flow field 
	if(PlayerPos.Equals(OldPlayerLocation))
		return;

	OldPlayerLocation = PlayerPos; 

	ResetNodeCosts(); 

	GridNode* TargetNode = Grid->GetNodeFromWorldLocation(PlayerPos);
	TargetNode->SetCost(0);

	// Better data structures can probably be used here 
	TArray<GridNode*> ToBeVisited; // Holds node that should be visited
	TSet<GridNode*> Visited; 

	ToBeVisited.Add(TargetNode);

	while(!ToBeVisited.IsEmpty())
	{
		// Set current to the first item in the array, then remove it 
		GridNode* Current = ToBeVisited[0];
		ToBeVisited.RemoveAt(0);
		Visited.Add(Current); // and add to visited 

		// For each neighbouring node 
		for(auto NeighbourNode : Grid->GetNeighbours(Current))
		{
			// Check if it's walkable, TODO: AI can get stuck in unwalkable nodes when moving diagonally (I think)
			// TODO: so the unwalkable nodes prob also needs a direction, for now I just set it towards the current node 
			if(!NeighbourNode->IsWalkable())
			{
				NeighbourNode->SetDirection(Current);
				continue;
			}

			// Get cost to travel to neighbor from current node (diagonal = 14, otherwise 10)
			const int NeighbourNewCost = CostToNode(Current, NeighbourNode) + Current->GetCost();
			// If path to node is cheaper than its current cost 
			if(NeighbourNewCost < NeighbourNode->GetCost())
			{
				// Add node to be visited if has not already been 
				if(!Visited.Contains(NeighbourNode))
					ToBeVisited.Add(NeighbourNode);

				// Update cost 
				NeighbourNode->SetCost(NeighbourNewCost);

				// Set direction to Current node 
				NeighbourNode->SetDirection(Current);

				// DEBUGGING DISPLAYING DIRECTION
				if(Grid->bDrawDebugStuff)
					DrawDebugLine(Grid->GetWorld(), Current->GetWorldCoordinate() + FVector::UpVector * 10,
					Current->GetWorldCoordinate() + Current->GetDirection() * 20 + FVector::UpVector * 10,
					FColor::Cyan, false, -1, 0, 5);
			}
		}
	}
}

void Pathfinder::ResetNodeCosts()
{
	for(int x = 0; x < Grid->GridArrayLengthX; x++)
		for(int y = 0; y < Grid->GridArrayLengthY; y++)
			Grid->GetNodeFromArray(x, y)->SetCost(INT_MAX); 
}