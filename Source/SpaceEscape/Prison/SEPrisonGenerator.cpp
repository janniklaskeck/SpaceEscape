// Fill out your copyright notice in the Description page of Project Settings.

#include "SEPrisonGenerator.h"
#include "SERoomList.h"

ASEPrisonGenerator::ASEPrisonGenerator()
{
	PrimaryActorTick.bCanEverTick = true;

}

void ASEPrisonGenerator::BeginPlay()
{
	Super::BeginPlay();
}

void ASEPrisonGenerator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASEPrisonGenerator::BuildPrison()
{
	if (MaxRooms < MinRooms)
	{
		MaxRooms = MinRooms;
	}
	PlacePrisonCell();
	int32 RoomsToPlace = FMath::RandRange(MinRooms, MaxRooms);
	for (int32 Index = 0; Index < RoomsToPlace; Index++)
	{
		TSubclassOf<ASERoomBase> NextRoomClass = RoomList->GetRandomPrisonMainRoom();
		ASERoomBase* PreviousRoom = PrisonCellRoom;
		if (Index > 0)
		{
			PreviousRoom = PlacedRooms[Index - 1];
		}
		PlaceRoom(NextRoomClass, PreviousRoom);
	}
}

TArray<int32> ASEPrisonGenerator::GenerateUniqueRoomCode(int32 Length /*= 3*/) const
{
	TArray<int32> GeneratedCode;

	bool HasUnqiqueCode = false;
	while (!HasUnqiqueCode)
	{
		for (int32 Index = 0; Index < Length; Index++)
		{
			GeneratedCode.Add(FMath::RandRange(0, 9));
		}
		bool CodeAlreadyUsed = false;
		for (ASERoomBase* Room : PlacedRooms)
		{
			if (Room->HasSameCode(GeneratedCode))
			{
				CodeAlreadyUsed = true;
			}
		}
		HasUnqiqueCode = !CodeAlreadyUsed;
	}
	return GeneratedCode;
}

ASEPrisonCell* ASEPrisonGenerator::GetPrisonCellRoom() const
{
	return PrisonCellRoom;
}


void ASEPrisonGenerator::PlacePrisonCell()
{
	TSubclassOf<ASEPrisonCell> RoomClass = RoomList->GetRandomPrisonCell();
	PrisonCellRoom = GetWorld()->SpawnActor<ASEPrisonCell>(RoomClass, FVector::ZeroVector, FRotator::ZeroRotator);
	PrisonCellRoom->PrisonGenerator = this;
	PrisonCellRoom->Init();
}

void ASEPrisonGenerator::PlaceRoom(TSubclassOf<class ASERoomBase> RoomClass, class ASERoomBase* PreviousRoom)
{
	ASERoomBase* NewRoom = GetWorld()->SpawnActor<ASERoomBase>(RoomClass, FVector::ZeroVector, FRotator::ZeroRotator);
	FVector PreviousRoomExit = PreviousRoom->GetForwardExit()->GetComponentLocation();
	FVector Location = PreviousRoomExit - NewRoom->GetEntry()->GetRelativeTransform().GetLocation();
	NewRoom->SetActorLocation(Location);
	NewRoom->PrisonGenerator = this;
	NewRoom->Init();
	PlacedRooms.Add(NewRoom);
}

