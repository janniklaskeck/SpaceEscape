// Fill out your copyright notice in the Description page of Project Settings.

#include "SEUtility.h"
#include "Kismet/GameplayStatics.h"
#include "SEMainGameMode.h"
#include "SEGameInstance.h"
#include "SEPrisonGenerator.h"
#include "SEGameState.h"
#include "SERoomBase.h"
#include "SEPlayerController.h"

class ASEMainGameMode* USEUtility::GetSEMainGameMode(UObject* WorldContextObject)
{
	return Cast<ASEMainGameMode>(UGameplayStatics::GetGameMode(WorldContextObject));
}

class USEGameInstance* USEUtility::GetSEGameInstance(UObject* WorldContextObject)
{
	return Cast<USEGameInstance>(UGameplayStatics::GetGameInstance(WorldContextObject));
}

class ASEGameState* USEUtility::GetSEGameState(UObject* WorldContextObject)
{
	return Cast<ASEGameState>(UGameplayStatics::GetGameState(WorldContextObject));
}

class ASEPlayerController* USEUtility::GetLocalSEPlayerController(UObject* WorldContextObject)
{
	return Cast<ASEPlayerController>(UGameplayStatics::GetPlayerController(WorldContextObject, 0));
}

class ASEPrisonGenerator* USEUtility::GetPrisonGenerator(UObject* WorldContextObject)
{
	TArray<AActor*> PrisonGens;
	UGameplayStatics::GetAllActorsOfClass(WorldContextObject, ASEPrisonGenerator::StaticClass(), PrisonGens);
	if (PrisonGens.Num() > 0)
		return Cast<ASEPrisonGenerator>(PrisonGens[0]);
	return nullptr;
}

class ASERoomBase* USEUtility::GetRoomWithCode(UObject* WorldContextObject, TArray<int32> Code)
{
	TArray<AActor*> Rooms;
	UGameplayStatics::GetAllActorsOfClass(WorldContextObject, ASERoomBase::StaticClass(), Rooms);
	if (Rooms.Num() > 0)
	{
		for (int32 Index = 0; Index < Rooms.Num(); Index++)
		{
			ASERoomBase* Room = Cast<ASERoomBase>(Rooms[Index]);
			if (Room->HasSameCode(Code))
			{
				return Room;
			}
		}
	}
	return nullptr;
}

int32 USEUtility::GetRandRangeWithout(int32 Min, int32 Max, TArray<int32> Exceptions)
{
	if (Min >= Max)
	{
		return Min;
	}
	else if (Exceptions.Num() == 0)
	{
		return FMath::RandRange(Min, Max);
	}
	TArray<int32> PossibleValues;
	for (int32 Index = Min; Index <= Max; Index++)
	{
		PossibleValues.Add(Index);
	}
	for (int32 Exception : Exceptions)
	{
		PossibleValues.Remove(Exception);
	}
	if (PossibleValues.Num() == 0)
	{
		return 0;
	}
	return PossibleValues[FMath::RandRange(0, PossibleValues.Num() - 1)];
}
