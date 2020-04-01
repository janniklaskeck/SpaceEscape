// Fill out your copyright notice in the Description page of Project Settings.

#include "SERoomList.h"

TSubclassOf<ASEPrisonCell> USERoomList::GetRandomPrisonCell()
{
	if (PrisonCellRooms.Num() == 0)
	{
		return nullptr;
	}
	return PrisonCellRooms[FMath::RandRange(0, PrisonCellRooms.Num() - 1)];
}

TSubclassOf<ASERoomBase> USERoomList::GetRandomPrisonMainRoom()
{
	if (PrisonMainRooms.Num() == 0)
	{
		return nullptr;
	}
	return PrisonMainRooms[FMath::RandRange(0, PrisonMainRooms.Num() - 1)];
}
