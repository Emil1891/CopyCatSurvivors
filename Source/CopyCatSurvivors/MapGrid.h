// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GridNode.h"
#include "Pathfinder.h"
#include "GameFramework/Actor.h"
#include "MapGrid.generated.h"

UCLASS()
class COPYCATSURVIVORS_API AMapGrid : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMapGrid();

	~AMapGrid() override; 

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaSeconds) override;

	UFUNCTION(BlueprintCallable)
	FVector GetDirectionBasedOnWorldLocation(const FVector WorldLoc) { return GetNodeFromWorldLocation(WorldLoc)->GetDirection(); }

private:

#pragma region DataMembers
	
	// 1D array (will be used as if it was 2D) keeping track of all nodes,
	// Unreal does not seem to like creating 2D arrays with Array[][] 
	// https://stackoverflow.com/a/2151141 (source to convert 2D array to 1D) 
	GridNode* Nodes; 

	// Radius for each node, smaller radius means more accurate but more performance expensive 
	UPROPERTY(EditAnywhere)
	float NodeRadius = 50.f;
	
	float NodeDiameter;  

	// The size of the grid 
	UPROPERTY(EditAnywhere)
	FVector2D GridSize = FVector2D(100, 100);

	// Holds the array sizes 
	int GridArrayLengthX;
	int GridArrayLengthY;

	FVector GridBottomLeftLocation; 

	// Not used as of now since that method did not seem to work 
	UPROPERTY(EditAnywhere)
	TArray<TEnumAsByte<EObjectTypeQuery>> UnwalkableObjects;

	// What is used instead to check if a node is walkable (actor checks overlaps)
	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> OverlapCheckActorClass;

	friend class Pathfinder; 
	Pathfinder* Pathfind = nullptr; 

#pragma endregion

#pragma region Functions 

	void CreateGrid();

	void AddToArray(const int IndexX, const int IndexY, const GridNode Node);

	GridNode* GetNodeFromArray(const int IndexX, const int IndexY) const;

	GridNode* GetNodeFromWorldLocation(const FVector WorldLoc) const;

	TArray<GridNode*> GetNeighbours(const GridNode* Node) const;

	int GetIndex(const int IndexX, const int IndexY) const; 

#pragma endregion 

#pragma region Debugging

	UPROPERTY(EditAnywhere)
	bool bDrawDebugStuff = true; 
	
	void DrawDebugStuff();

#pragma endregion
	
};
