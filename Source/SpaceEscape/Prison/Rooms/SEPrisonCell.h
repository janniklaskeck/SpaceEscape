// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Prison/Rooms/SERoomBase.h"
#include "SEPrisonCell.generated.h"

/**
 *
 */
UCLASS()
class SPACEESCAPE_API ASEPrisonCell : public ASERoomBase
{
	GENERATED_BODY()
public:
	ASEPrisonCell();
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class USceneComponent* SpawnLocation;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class UChildActorComponent* CellDoor;

public:
	void Init() override;
	class USceneComponent* GetSpawnLocation() const
	{
		return SpawnLocation;
	}
	class ASEPuzzleBase* GetRoomPuzzle() override;
};
