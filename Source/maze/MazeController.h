// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MazeController.generated.h"

UCLASS()
class MAZE_API AMazeController : public AActor
{
	GENERATED_BODY()
    public:

        AMazeController();

    protected:

        UPROPERTY(EditDefaultsOnly, Category = "Maze Settings")
        TSubclassOf<class AMazebox> CellToSwapClass = nullptr;

        UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Maze Settings")
        int32 ColumnNumber = 8;

        UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Maze Settings")
        int32 RowNumber = 9;

        UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Maze Settings")
        float DistanceXBetweenCells = 300;

        UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Maze Settings")
        float DistanceYBetweenCells = 300;

        UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Maze Settings")
        float WaitTimeBetweenCreateCells = 0.5f;

    protected:

        virtual void BeginPlay() override;

    public:

        virtual void Tick(float DeltaTime) override;


    private:

        TArray<AMazebox*> CellList;
        
        bool bRandomizeMaze = false;
        float CurrentDeltaTime = 0.0f;

        int32 VisitedCells;
        TArray<int32> CellStack;
        int32 CurrentIndexCell;

    private:

        int32 GetAdjacentCellWithWalls(const int32& IndexCell);

    };
