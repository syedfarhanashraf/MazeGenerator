// Fill out your copyright notice in the Description page of Project Settings.

#include "Mazebox.h"
#include "MazeController.h"

// Sets default values
AMazeController::AMazeController()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMazeController::BeginPlay()
{
	Super::BeginPlay();
    
	FVector SpawnPosition = GetActorLocation();

    for (int iRow = 0; iRow < RowNumber; ++iRow)
    {
        SpawnPosition.X = GetActorLocation().X;

        for (int iCol = 0; iCol < ColumnNumber; ++iCol)
        {
            // Spawn each cell
            FActorSpawnParameters SpawnParamenters;
            SpawnParamenters.Owner = this;
            //SpawnParamenters.Instigator = Instigator;

            AMazebox* SpawnedCell = GetWorld()->SpawnActor<AMazebox>(CellToSwapClass, SpawnPosition, FRotator::ZeroRotator, SpawnParamenters);

            if (SpawnedCell != nullptr)
            {
                // Attach cell to this ator
                SpawnedCell->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform);

                int32 CellIndex = iRow * ColumnNumber + iCol;

                SpawnedCell->Initialize(iRow, iCol, CellIndex);

                CellList.Add(SpawnedCell);
            }

            SpawnPosition.X += DistanceXBetweenCells;
        }

        SpawnPosition.Y += DistanceYBetweenCells;
    }

    // Generate Random cell to start with
    int32 RandomRow = FMath::RandRange(0, RowNumber - 1);
    int32 RandomCol = FMath::RandRange(0, ColumnNumber - 1);

    CurrentIndexCell = RandomRow * ColumnNumber + RandomCol;

    // Create first cell
    CellList[CurrentIndexCell]->SetIsCreated(true);
    CellList[CurrentIndexCell]->ShowFloor();
    CellList[CurrentIndexCell]->ShowWall(0);
    CellList[CurrentIndexCell]->ShowWall(1);
    CellList[CurrentIndexCell]->ShowWall(2);
    CellList[CurrentIndexCell]->ShowWall(3);

    // Add that cell to the cellStack
    CellStack.Push(CurrentIndexCell);
    VisitedCells = 1;
    // Start randomizing the maze
    bRandomizeMaze = true;}

// Called every frame
void AMazeController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    if (bRandomizeMaze)
        {
            CurrentDeltaTime += DeltaTime;

            if (CurrentDeltaTime > WaitTimeBetweenCreateCells)
            {
                CurrentDeltaTime = 0.0f;

                if (VisitedCells < CellList.Num())
                {
                    UE_LOG(LogTemp, Warning, TEXT("Adding Cell: %d / %d  "), CellStack.Num(), CellList.Num());

                    // Find neighbour and create passage for that cell
                    int32 NextIndexCell = GetAdjacentCellWithWalls(CurrentIndexCell);

                    if (NextIndexCell > -1)
                    {
                        // Push the current cell to the
                        CellStack.Push(CurrentIndexCell);
                        CurrentIndexCell = NextIndexCell;
                        VisitedCells++;
                    }
                    else
                    {
                        // Get from the stack
                        if (CellStack.Num() > 0)
                        {
                            CurrentIndexCell = CellStack.Pop();
                        }
                        else
                        {
                            VisitedCells = CellList.Num();

                            UE_LOG(LogTemp, Warning, TEXT("Random Maze generation completed"));

                            bRandomizeMaze = false;
                        }
                    }

                    CurrentDeltaTime = 0.0f;
                }
                else
                {
                    VisitedCells = CellList.Num();
                    bRandomizeMaze = false;
                    CellList[0]->HideWall(1);
                      // Or HideWall(1)
                    CellList[RowNumber * ColumnNumber - 1]->HideWall(1); // Or HideWall(1)
                    UE_LOG(LogTemp, Warning, TEXT("Random Maze generation completed"), CellStack.Num());
                }
            }
        }
    }

int32 AMazeController::GetAdjacentCellWithWalls(const int32& IndexCell)
{
    TArray<int32> NeighbourCells;
    TArray<int32> Directions; // To store each the direction


    // Coordinates for the given cell
    int32 Col = CellList[IndexCell]->GetCoords().X;
    int32 Row = CellList[IndexCell]->GetCoords().Y;

    // Add available directions
    // To top
    //Row -= 1;
    if ((Row - 1) >= 0)
    {
        int32 Next = (Row - 1) * ColumnNumber + Col;

        if (CellList[Next]->AllWallsIntact()) // All walls up for this cell
        {
            Directions.Add(0);
            NeighbourCells.Add(Next);
        }
    }

    // To Bottom
    if ((Row + 1) < RowNumber)
    {
        int32 Next = (Row + 1) * ColumnNumber + Col;

        if (CellList[Next]->AllWallsIntact()) // All walls up for this cell
        {
            Directions.Add(1);
            NeighbourCells.Add(Next);
        }
    }

    // To Left
    if ((Col - 1) >= 0)
    {
        int32 Next = Row * ColumnNumber + (Col - 1);

        if (CellList[Next]->AllWallsIntact()) // All walls up for this cell
        {
            Directions.Add(2);
            NeighbourCells.Add(Next);
        }
    }

    // To Right
    if ((Col + 1) < ColumnNumber)
    {
        int32 Next = Row * ColumnNumber + (Col + 1);

        if (CellList[Next]->AllWallsIntact()) // All walls up for this cell
        {
            Directions.Add(3);
            NeighbourCells.Add(Next);
        }
    }

    int32 NextCellIndex = -1;

    // Select random direction among the available ones
    if (NeighbourCells.Num() > 0)
    {
        int32 RandomDirection = FMath::RandRange(0, Directions.Num() - 1);

        // Knocked down direction between the current cell and next cell
        NextCellIndex = NeighbourCells[RandomDirection];


        // Check if that cell hasn't been created (or visible)
        if (!CellList[NextCellIndex]->GetIsCreated())
        {
            CellList[NextCellIndex]->SetIsCreated(true);
            // Show floor and walls
            CellList[NextCellIndex]->ShowFloor();

            CellList[NextCellIndex]->ShowWall(0);
            CellList[NextCellIndex]->ShowWall(1);
            CellList[NextCellIndex]->ShowWall(2);
            CellList[NextCellIndex]->ShowWall(3);

        }

        // Pick the cell as a current cell
        switch (Directions[RandomDirection])
        {
        case 0: // To top
            CellList[NextCellIndex]->CreatePassage(1); // KnockDown back wall (opposite)
            CellList[IndexCell]->CreatePassage(0);// KnockDown front wall
            break;

        case 1: // To down
            CellList[NextCellIndex]->CreatePassage(0); //  KnockDown front wall  (opposite)
            CellList[IndexCell]->CreatePassage(1); // KnockDown back wall
            break;

        case 2: // To left
            CellList[NextCellIndex]->CreatePassage(3); // KnockDown right wall  (opposite)
            CellList[IndexCell]->CreatePassage(2);// KnockDown left wall
            break;

        case 3: // To right
            CellList[NextCellIndex]->HideWall(2);  // KnockDown left wall (opposite)
            CellList[IndexCell]->HideWall(3);// KnockDown right wall
            break;
        }

    }
    return NextCellIndex;
}

