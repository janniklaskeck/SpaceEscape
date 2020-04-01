// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SEPrisonGenerator.generated.h"

UCLASS()
class SPACEESCAPE_API ASEPrisonGenerator : public AActor
{
	GENERATED_BODY()
public:
	ASEPrisonGenerator();

	UPROPERTY(EditDefaultsOnly, meta = (ClampMin = "0", UIMin = "0"))
		int32 MinRooms;
	UPROPERTY(EditDefaultsOnly, meta = (ClampMin = "0", UIMin = "0"))
		int32 MaxRooms;

	UPROPERTY(EditDefaultsOnly)
		class USERoomList* RoomList;

protected:
	void BeginPlay() override;
	void Tick(float DeltaTime) override;
public:
	void BuildPrison();

	TArray<int32> GenerateUniqueRoomCode(int32 Length = 3) const;
	class ASEPrisonCell* GetPrisonCellRoom() const;
	class ASERoomBase* GetRoomWithCode(TArray<int32> Code);
protected:
	void PlacePrisonCell();
	void PlaceRoom(TSubclassOf<class ASERoomBase> RoomClass, class ASERoomBase* PreviousRoom);

	class ASEPrisonCell* PrisonCellRoom;
	TArray<class ASERoomBase*> PlacedRooms;
};
