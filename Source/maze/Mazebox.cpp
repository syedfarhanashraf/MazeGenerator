// Fill out your copyright notice in the Description page of Project Settings.


#include "Mazebox.h"

// Sets default values
AMazebox::AMazebox()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    RootScene = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
    RootComponent = RootScene;

    Floor = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Floor"));
    Floor->SetupAttachment(RootComponent);

    Wall_Front = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Wall_Front"));
    Wall_Front->SetupAttachment(RootComponent);
    Wall_Back = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Wall_Back"));
    Wall_Back->SetupAttachment(RootComponent);
    

    Wall_Left = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Wall_Left"));
    Wall_Left->SetupAttachment(RootComponent);
    Wall_Right = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Wall_Right"));
    Wall_Right->SetupAttachment(RootComponent);
    
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMazebox::BeginPlay()
{
	Super::BeginPlay();
	NumberWallsUp = 4;
    bCreated = false;

    Floor->SetVisibility(false, true);
    Wall_Front->ToggleVisibility(false);
    Wall_Right->ToggleVisibility(false);
    Wall_Left->ToggleVisibility(false);
    Wall_Back->ToggleVisibility(false);
}

// Called every frame

void AMazebox::Initialize(int32 Row, int32 Column, int32 Index)
{
    bCreated = false;

    RowIndex = Row;
    ColumnIndex = Column;

    NumberWallsUp = 4;

//    if (DebugText != nullptr)
//    {
//        FString Text = FString::FromInt(Index) + " = (" + FString::FromInt(RowIndex) + "," + FString::FromInt(ColumnIndex) + ")";
//        DebugText->SetText(FText::FromString(Text));
//    }
}
void AMazebox::HideFloor()
{
    Floor->SetVisibility(false, true);
}

void AMazebox::ShowFloor()
{
    Floor->SetVisibility(true, true);
}

void AMazebox::ShowWall(int32 WallIndex)
{
    switch (WallIndex)
    {
    case 0:
        Wall_Front->ToggleVisibility(true); // Front Wall (ToTop)
        break;
    case 1:
        Wall_Back->ToggleVisibility(true); // Back wall (ToDown)
        break;
    case 2:
        Wall_Left->ToggleVisibility(true); // Left wall (ToLeft)
        break;
    case 3:
        Wall_Right->ToggleVisibility(true); // Right wall (ToRight)
        break;
    }
}

void AMazebox::HideWall(int32 WallIndex)
{
    switch (WallIndex)
    {
    case 0:
        Wall_Front->ToggleVisibility(false); // Front Wall (ToTop)
        break;
    case 1:
        Wall_Back->ToggleVisibility(false); // Back wall (ToDown)
        break;
    case 2:
        Wall_Left->ToggleVisibility(false); // Left wall (ToLeft)
        break;
    case 3:
        Wall_Right->ToggleVisibility(false); // Right wall (ToRight)
        break;
    }
}


void AMazebox::CreatePassage(int32 WallIndex)
{
    switch (WallIndex)
    {
    case 0:
        Wall_Front->ToggleVisibility(false); // Front Wall (ToTop)
        NumberWallsUp -= 1;
        break;
    case 1:
        Wall_Back->ToggleVisibility(false); // Back wall (ToDown)
        NumberWallsUp -= 1;
        break;
    case 2:
        Wall_Left->ToggleVisibility(false); // Left wall (ToLeft)
        NumberWallsUp -= 1;
        break;
    case 3:
        Wall_Right->ToggleVisibility(false); // Right wall (ToRight)
        NumberWallsUp -= 1;
        break;
    }
}
