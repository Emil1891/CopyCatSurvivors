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
	GridNode* PlayerNode = Grid->GetNodeFromWorldLocation(PlayerPos);

	// If player has not moved (standing in same node), no need to update the flow field 
	if(PlayerNode == OldPlayerNode)
		return;

	OldPlayerNode = PlayerNode; 

	ResetNodeCosts(); 

	GridNode* TargetNode = Grid->GetNodeFromWorldLocation(PlayerPos);
	TargetNode->SetCost(0);

	// Better data structure can probably be used here 
	TArray<GridNode*> ToBeVisited; // Holds node that should be visited (Queue instead? needs fast removal at start)

	ToBeVisited.Add(TargetNode);

	while(!ToBeVisited.IsEmpty())
	{
		// Set current to the first item in the array, then remove it 
		GridNode* Current = ToBeVisited[0];
		ToBeVisited.RemoveAt(0);

		// For each neighbouring node 
		for(auto NeighbourNode : Grid->GetNeighbours(Current))
		{
			// Check if it's walkable, if it is, set its direction to nearest walkable node so if AI walks into an
			// unwalkable node, it will be repelled away. i dont know if this is the best solution to the problem
			if(!NeighbourNode->IsWalkable()) 
			{
				// their direction only needs to be set once, assuming the map does not change 
				if(bHasSetDirInUnwalkableNodes)
					continue;
				
				// if not set, then set 
				SetDirectionInUnwalkableNode(NeighbourNode);
			}

			// Get cost to travel to neighbor from current node (diagonal = 14, otherwise 10)
			const int NeighbourNewCost = CostToNode(Current, NeighbourNode) + Current->GetCost();
			// If path to node is cheaper than its current cost 
			if(NeighbourNewCost < NeighbourNode->GetCost())
			{
				// Add node to be visited, since its neighbours need to be checked if they
				// also have a cheaper path through this node 
				ToBeVisited.Add(NeighbourNode);

				// Update cost 
				NeighbourNode->SetCost(NeighbourNewCost);

				// Set direction to Current node 
				NeighbourNode->SetDirection(Current);

				// DEBUGGING DISPLAYING DIRECTION
				if(Grid->bDrawDebugStuff)
					DrawDebugLine(Grid->GetWorld(), Current->GetWorldCoordinate() + FVector::UpVector * 10,
					Current->GetWorldCoordinate() + Current->GetDirection() * 20 + FVector::UpVector * 10,
					FColor::Cyan, false, 0.2, 0, 5); 
			}
		}
	}
	bHasSetDirInUnwalkableNodes = true; // set to true so it is only checked/set once 
}

void Pathfinder::SetDirectionInUnwalkableNode(GridNode* NeighbourNode)
{
	// set lowest cost away to int max 
	int LowestCostAwayFromNode = INT_MAX;
	// then visit each neighbour 
	for(const auto NeighbourToNeighbour : Grid->GetNeighbours(NeighbourNode))
	{
		// if neighbour is walkable and has a lower cost than lowest
		const int CostToNeighbour = CostToNode(NeighbourNode, NeighbourToNeighbour); 
		if(NeighbourToNeighbour->IsWalkable() && CostToNeighbour < LowestCostAwayFromNode)
		{
			// then set direction to that neighbouring node 
			NeighbourNode->SetDirection(NeighbourToNeighbour);
			LowestCostAwayFromNode = CostToNeighbour; 
		}
	}

	// DEBUGGING DRAWING DIRECTION IN UNWALKABLE NODES 
	if(Grid->bDrawDebugStuff)
		DrawDebugLine(Grid->GetWorld(), NeighbourNode->GetWorldCoordinate() + FVector::UpVector * 10,
		NeighbourNode->GetWorldCoordinate() + NeighbourNode->GetDirection() * 20 + FVector::UpVector * 10,
		FColor::Cyan, true, -1, 0, 5);
}

void Pathfinder::ResetNodeCosts()
{
	for(int x = 0; x < Grid->GridArrayLengthX; x++)
		for(int y = 0; y < Grid->GridArrayLengthY; y++)
			Grid->GetNodeFromArray(x, y)->SetCost(INT_MAX); 
}
