// Fill out your copyright notice in the Description page of Project Settings.

#include "SELabyrinthRoom.h"
#include "Labyrinth/SEFloorLabyrinth.h"

ASELabyrinthRoom::ASELabyrinthRoom()
{
	FloorLabyrinth = CreateDefaultSubobject<UChildActorComponent>("FloorLabyrinth");
	FloorLabyrinth->SetupAttachment(RootComponent);
}

void ASELabyrinthRoom::Init()
{
	Super::Init();
	if (FloorLabyrinth->GetChildActor())
	{
		GetRoomPuzzle()->InitPuzzle();
	}

}

class ASEPuzzleBase* ASELabyrinthRoom::GetRoomPuzzle()
{
	return Cast<ASEPuzzleBase>(FloorLabyrinth->GetChildActor());
}
