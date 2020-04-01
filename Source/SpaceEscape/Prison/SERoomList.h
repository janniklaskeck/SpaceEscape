// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "SEPrisonCell.h"
#include "SERoomList.generated.h"

UCLASS()
class SPACEESCAPE_API USERoomList : public UDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly)
		TArray<TSubclassOf<ASEPrisonCell>> PrisonCellRooms;

	UPROPERTY(EditDefaultsOnly)
		TArray<TSubclassOf<ASERoomBase>> PrisonMainRooms;
	UPROPERTY(EditDefaultsOnly)
		TArray<TSubclassOf<ASERoomBase>> PrisonSideRooms;

	TSubclassOf<ASEPrisonCell> GetRandomPrisonCell();
	TSubclassOf<ASERoomBase> GetRandomPrisonMainRoom();
};
