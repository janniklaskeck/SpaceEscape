// Fill out your copyright notice in the Description page of Project Settings.

#include "SEPrisonCell.h"
#include "Components/ChildActorComponent.h"
#include "ColorDoor/SEColorDoor.h"

ASEPrisonCell::ASEPrisonCell()
{
	SpawnLocation = CreateDefaultSubobject<USceneComponent>("SpawnLocation");
	SpawnLocation->SetupAttachment(RootComponent);

	CellDoor = CreateDefaultSubobject<UChildActorComponent>("CellDoor");
	CellDoor->SetupAttachment(RootComponent);
}

void ASEPrisonCell::Init()
{
	Super::Init();

	ASEColorDoor* ColorDoor = Cast<ASEColorDoor>(CellDoor->GetChildActor());
	if (ColorDoor)
		ColorDoor->InitPuzzle();
}

class ASEPuzzleBase* ASEPrisonCell::GetRoomPuzzle()
{
	return Cast<ASEPuzzleBase>(CellDoor->GetChildActor());
}
