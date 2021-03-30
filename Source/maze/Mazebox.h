// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Mazebox.generated.h"

UCLASS()
class MAZE_API AMazebox : public AActor
{
	GENERATED_BODY()
    
	protected:

        UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MazeCell")
        class USceneComponent* RootScene;

        UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MazeCell")
        class UStaticMeshComponent* Floor;

        UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MazeCell")
        class UStaticMeshComponent* Wall_Front; // Front Wall
        UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MazeCell")
        class UStaticMeshComponent* Wall_Back; // Back Wall
        UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MazeCell")
        class UStaticMeshComponent* Wall_Left; // Left Wall
        UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MazeCell")
        class UStaticMeshComponent* Wall_Right; // Right Wall

        

       


        UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "MazeCell")
        class UTextRenderComponent* DebugText;

    public:

        AMazebox();

    protected:

        virtual void BeginPlay() override;

    public:


        void Initialize(int32 Row, int32 Column, int32 Index);

        FORCEINLINE bool GetIsCreated() { return bCreated; };
        FORCEINLINE void SetIsCreated(bool Value) { bCreated = Value; };

        FORCEINLINE bool AllWallsIntact() { return (NumberWallsUp >= 4); };


        void HideFloor();

        void ShowFloor();

        void ShowWall(int32 WallIndex);

        void HideWall(int32 WallIndex);

        void CreatePassage(int32 WallIndex);


        FORCEINLINE FVector2D GetCoords()
        {
            return FVector2D(ColumnIndex, RowIndex); // X, Y
        }

    private:
        bool bCreated;

        int32 ColumnIndex;
        int32 RowIndex;
        int32 NumberWallsUp = 0;
  


};
