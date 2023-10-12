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

	// Returns the direction in the node that the WorldLocation is in 
	UFUNCTION(BlueprintCallable)
	FVector GetDirectionBasedOnWorldLocation(const FVector WorldLoc) { return GetNodeFromWorldLocation(WorldLoc)->GetDirection(); }

	// Returns the node that the World Location is in 
	GridNode* GetNodeFromWorldLocation(const FVector WorldLoc) const;
	
	FVector GetGridBottomLeftLocation() const { return GridBottomLeftLocation; }

	FVector2D GetGridSize() const { return GridSize; }

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

	// What object types that should be considered as unwalkable  
	UPROPERTY(EditAnywhere)
	TArray<TEnumAsByte<EObjectTypeQuery>> UnwalkableObjects { TEnumAsByte<EObjectTypeQuery>::EnumType::ObjectTypeQuery1 };

	friend class Pathfinder; 
	Pathfinder* Pathfind = nullptr;

#pragma endregion

#pragma region Functions 

	void CreateGrid();

	void AddToArray(const int IndexX, const int IndexY, const GridNode Node);

	GridNode* GetNodeFromArray(const int IndexX, const int IndexY) const;

	TArray<GridNode*> GetNeighbours(const GridNode* Node) const;

	int GetIndex(const int IndexX, const int IndexY) const; 

#pragma endregion 

#pragma region Debugging

	UPROPERTY(EditAnywhere)
	bool bDrawDebugGrid = true; 
	
	void DrawDebugGrid();

#pragma endregion
	
};
