// Fill out your copyright notice in the Description page of Project Settings.

#include "MapGrid.h"

#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

// Sets default values
AMapGrid::AMapGrid()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true; 
	
}

AMapGrid::~AMapGrid()
{
	// does unreal handle this with its garbage collection? 
	delete [] Nodes;
	delete Pathfind; 
}

// Called when the game starts or when spawned
void AMapGrid::BeginPlay()
{
	Super::BeginPlay();

	NodeDiameter = NodeRadius * 2;
	
	CreateGrid();
	
	if(bDrawDebugStuff)
		DrawDebugStuff();

	Pathfind = new Pathfinder(UGameplayStatics::GetPlayerPawn(this, 0), this);
	
	UE_LOG(LogTemp, Warning, TEXT("diameter: %f"), NodeDiameter)
	UE_LOG(LogTemp, Warning, TEXT("Grid Length: (X: %i, Y: %i)"), GridArrayLengthX, GridArrayLengthY)
	UE_LOG(LogTemp, Warning, TEXT("GridSize: %s"), *GridSize.ToString())
}

void AMapGrid::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	Pathfind->UpdateNodeDirections(); 
}

void AMapGrid::CreateGrid()
{
	GridArrayLengthX = FMath::RoundToInt(GridSize.X / NodeRadius);
	GridArrayLengthY = FMath::RoundToInt(GridSize.Y / NodeRadius);

	Nodes = new GridNode[GridArrayLengthX * GridArrayLengthY]; 

	// The grid's pivot is in the center, need its position as if pivot was in the bottom left corner 
	FVector GridBottomLeft = GetActorLocation();
	GridBottomLeft.X -= GridSize.X;
	GridBottomLeft.Y -= GridSize.Y;

	GridBottomLeftLocation = GridBottomLeft; 

	TArray<AActor*> ActorsToIgnore;
	TArray<AActor*> OverlappingActors;
	
	auto OverlapActor = GetWorld()->SpawnActor<AActor>(OverlapCheckActorClass, GetActorLocation(), FRotator::ZeroRotator); 

	for(int x = 0; x < GridArrayLengthX; x++)
	{
		for(int y = 0; y < GridArrayLengthY; y++)
		{
			FVector NodePos = GridBottomLeft;
			NodePos.X += x * NodeDiameter + NodeRadius; // Pos now in node center 
			NodePos.Y  += y * NodeDiameter + NodeRadius;

			// The lines below would be better but they dont seem to work? Should try again when a level is in place
			// because they seem to detect some (handplaced?) objects? 
			// const bool bAreaWalkable = UKismetSystemLibrary::SphereOverlapActors(this, NodePos,
			// 	NodeRadius, UnwalkableObjects, UClass::StaticClass(), ActorsToIgnore,OverlappingActors);

			// AddToArray(x, y, GridNode(bAreaWalkable, NodePos));
			
			// This is currently a work around to above but it works fine as of now, but adjusting node radius
			// requires adjusting the Overlapping actor's mesh's size manually. solution above would not require it
			OverlapActor->SetActorLocation(NodePos);
			OverlapActor->GetOverlappingActors(OverlappingActors);

			AddToArray(x, y, GridNode(OverlappingActors.IsEmpty(), NodePos,  x, y)); 
			
		}
	}
	OverlapActor->Destroy(); 
}

void AMapGrid::AddToArray(const int IndexX, const int IndexY, const GridNode Node)
{
	const int Index = IndexX * GridArrayLengthX + IndexY; 
	Nodes[Index] = Node;
}

GridNode* AMapGrid::GetNodeFromArray(const int IndexX, const int IndexY)
{
	const int Index = IndexX * GridArrayLengthX + IndexY;
	return &Nodes[Index]; 
}

GridNode* AMapGrid::GetNodeFromWorldLocation(const FVector WorldLoc)
{
	const float GridRelativeX = WorldLoc.X  - GridBottomLeftLocation.X; // position relative to grids bottom left corner 
	const float GridRelativeY = WorldLoc.Y - GridBottomLeftLocation.Y; 

	// checks how many nodes "fit" in the relative position for array indexes 
	const int x = FMath::Clamp(FMath::RoundToInt((GridRelativeX / NodeDiameter) - NodeRadius), 0, GridArrayLengthX - 1);
	const int y = FMath::Clamp(FMath::RoundToInt((GridRelativeY / NodeDiameter) - NodeRadius), 0, GridArrayLengthY - 1);

	return GetNodeFromArray(x, y);
}

TArray<GridNode*> AMapGrid::GetNeighbours(const GridNode* Node)
{
	TArray<GridNode*> Neighbours;

	// -1 to plus 1 in each direction to get every neighbour node 
	for(int x = -1; x <= 1; x++)
	{
		for(int y = -1; y <= 1; y++)
		{
			if(x == 0 && y == 0) // itself 
				continue;

			int GridX = Node->GridX + x; // Grid indexes 
			int GridY = Node->GridY + y;

			// if any index is out of bounds 
			if(GridX < 0 || GridX > GridArrayLengthX - 1 || GridY < 0 || GridY > GridArrayLengthY - 1)
				continue;

			Neighbours.Add(GetNodeFromArray(GridX, GridY)); 
		}
	}

	return Neighbours; 
}

void AMapGrid::DrawDebugStuff()
{
	DrawDebugBox(GetWorld(), GetActorLocation(), FVector(GridSize.X, GridSize.Y, 1), FColor::Red);

	for(int x = 0; x < GridArrayLengthX; x++)
	{
		for(int y = 0; y < GridArrayLengthY; y++)
		{
			GridNode* Node = GetNodeFromArray(x, y);
			FColor Color = Node->IsWalkable() ? FColor::Green : FColor::Red; 
			DrawDebugBox(GetWorld(), Node->GetWorldCoordinate(), FVector(NodeRadius, NodeRadius, 1), Color, true);
		}
	}
}
