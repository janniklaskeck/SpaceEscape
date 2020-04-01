// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "SEDoorColors.generated.h"

USTRUCT(BlueprintType)
struct FSEDoorColorCombination
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly)
		int32 First;
	UPROPERTY(EditDefaultsOnly)
		int32 Second;
	UPROPERTY(EditDefaultsOnly)
		int32 Third;

	TArray<int32> AsArray() const
	{
		TArray<int32> Array;
		Array.Add(First);
		Array.Add(Second);
		Array.Add(Third);
		return Array;
	}
};

UCLASS(BlueprintType)
class SPACEESCAPE_API USEDoorColors : public UDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		TArray<FColor> Colors;

	UPROPERTY(EditDefaultsOnly)
		TArray<FSEDoorColorCombination> FirstPartCombinations;
	UPROPERTY(EditDefaultsOnly)
		TArray<FSEDoorColorCombination> SecondPartCombinations;
};
