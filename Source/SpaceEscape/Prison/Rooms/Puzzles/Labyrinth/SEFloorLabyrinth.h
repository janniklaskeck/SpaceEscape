// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Prison/Rooms/Puzzles/SEPuzzleBase.h"
#include "SEFloorLabyrinth.generated.h"

UCLASS()
class SPACEESCAPE_API ASEFloorLabyrinth : public ASEPuzzleBase
{
	GENERATED_BODY()
public:
	ASEFloorLabyrinth();
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		TArray<class ASELabyrinthTile*> Tiles;
	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<class ASELabyrinthTile> TileClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		float TileWidth = 100.f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		float TileGap = 10.f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		int32 TileGridWidth = 5;

	void BeginPlay() override;
public:
	void InitPuzzle() override;

	UFUNCTION(BlueprintCallable, BlueprintPure)
		TArray<class ASELabyrinthTile*> GetCorrectPath() const
	{
		return CorrectPath;
	}
private:
	class ASELabyrinthTile* GetTile(int32 XPos, int32 YPos) const;

private:
	UPROPERTY(EditDefaultsOnly)
		int32 MinPathLength = 10;
	UPROPERTY(EditDefaultsOnly)
		int32 MaxPathLength = 15;
	void ChoosePath();
	UPROPERTY(Replicated)
		TArray<class ASELabyrinthTile*> CorrectPath;
	TArray<class ASELabyrinthTile*> GetStartingTiles() const;
	class ASELabyrinthTile* GetRandomForwardTile(class ASELabyrinthTile* Origin) const;

	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
