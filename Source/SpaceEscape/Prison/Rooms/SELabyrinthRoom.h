// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Prison/Rooms/SERoomBase.h"
#include "SELabyrinthRoom.generated.h"

/**
 * 
 */
UCLASS()
class SPACEESCAPE_API ASELabyrinthRoom : public ASERoomBase
{
	GENERATED_BODY()
public:
	ASELabyrinthRoom();
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class UChildActorComponent* FloorLabyrinth;
public:
	void Init() override;

	class ASEPuzzleBase* GetRoomPuzzle() override;
};
