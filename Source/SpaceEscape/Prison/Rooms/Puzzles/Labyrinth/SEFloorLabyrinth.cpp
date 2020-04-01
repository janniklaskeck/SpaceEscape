// Fill out your copyright notice in the Description page of Project Settings.

#include "Labyrinth/SEFloorLabyrinth.h"
#include "Labyrinth/SELabyrinthTile.h"
#include "SELabyrinthRoom.h"
#include "Net/UnrealNetwork.h"

ASEFloorLabyrinth::ASEFloorLabyrinth()
{

}

void ASEFloorLabyrinth::BeginPlay()
{
	Super::BeginPlay();
}

void ASEFloorLabyrinth::InitPuzzle()
{
	Super::InitPuzzle();
	for (int32 XPos = 0; XPos < TileGridWidth; XPos++)
	{
		for (int32 YPos = 0; YPos < TileGridWidth; YPos++)
		{
			FVector Location = FVector(XPos * (TileWidth + TileGap), YPos * (TileWidth + TileGap), 0.f);
			Location += GetActorLocation();
			ASELabyrinthTile* Tile = GetWorld()->SpawnActor<ASELabyrinthTile>(TileClass, Location, FRotator::ZeroRotator);
			Tile->SetActorScale3D(FVector(TileWidth / 100.f, TileWidth / 100.f, 1.f));
			Tiles.Add(Tile);
			Tile->Init(YPos, XPos); // Flip X and Y for proper indices
			Tile->SetPrivateState(ESELabyrinthTileState::Wrong);
		}
	}
	ChoosePath();
}

class ASELabyrinthTile* ASEFloorLabyrinth::GetTile(int32 XPos, int32 YPos) const
{
	for (ASELabyrinthTile* Tile : Tiles)
	{
		if (Tile->GetPosition().XPos == XPos && Tile->GetPosition().YPos == YPos)
		{
			return Tile;
		}
	}
	return nullptr;
}

void ASEFloorLabyrinth::ChoosePath()
{
	int32 PathLength = FMath::RandRange(MinPathLength, MaxPathLength);
	int32 RandomStartIndex = FMath::RandRange(0, TileGridWidth - 1);
	ASELabyrinthTile* StartingTile = GetStartingTiles()[RandomStartIndex];
	for (ASELabyrinthTile* Tile : Tiles)
	{
		Tile->SetPrivateState(ESELabyrinthTileState::Wrong);
	}
	CorrectPath.Reset(10);
	CorrectPath.Add(StartingTile);
	StartingTile->SetPrivateState(ESELabyrinthTileState::Correct);
	ASELabyrinthTile* NextTile = StartingTile;
	while (NextTile->GetPosition().YPos != TileGridWidth - 1)
	{
		NextTile = GetRandomForwardTile(NextTile);
		if (!NextTile)
		{
			break;
			ChoosePath();
		}
		else
		{
			CorrectPath.Add(NextTile);
			NextTile->SetPrivateState(ESELabyrinthTileState::Correct);
		}
	}
}

TArray<class ASELabyrinthTile*> ASEFloorLabyrinth::GetStartingTiles() const
{
	TArray<ASELabyrinthTile*> StartingTiles;
	for (ASELabyrinthTile* Tile : Tiles)
	{
		if (Tile->GetPosition().YPos == 0)
		{
			StartingTiles.Add(Tile);
		}
	}
	return StartingTiles;
}

class ASELabyrinthTile* ASEFloorLabyrinth::GetRandomForwardTile(class ASELabyrinthTile* Origin) const
{
	TArray<ASELabyrinthTile*> PossibleDirections;
	FTilePosition OriginPosition = Origin->GetPosition();
	ASELabyrinthTile* ForwardTile = GetTile(OriginPosition.XPos, OriginPosition.YPos + 1);
	if (ForwardTile)
		PossibleDirections.Add(ForwardTile);

	if (OriginPosition.XPos > 0)
	{
		ASELabyrinthTile* LeftTile = GetTile(OriginPosition.XPos - 1, OriginPosition.YPos);
		if (!CorrectPath.Contains(LeftTile))
		{
			PossibleDirections.Add(LeftTile);
		}
	}
	if (OriginPosition.XPos < TileGridWidth - 1)
	{
		ASELabyrinthTile* RightTile = GetTile(OriginPosition.XPos + 1, OriginPosition.YPos);
		if (!CorrectPath.Contains(RightTile))
		{
			PossibleDirections.Add(RightTile);
		}
	}
	if (PossibleDirections.Num() == 0)
		return nullptr;

	return PossibleDirections[FMath::RandRange(0, PossibleDirections.Num() - 1)];
}

void ASEFloorLabyrinth::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ASEFloorLabyrinth, CorrectPath);
}
