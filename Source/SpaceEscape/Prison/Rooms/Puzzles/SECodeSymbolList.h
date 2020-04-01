// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "SECodeSymbolList.generated.h"

/**
 *
 */
UCLASS(BlueprintType)
class SPACEESCAPE_API USECodeSymbolList : public UDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		TArray<UTexture*> Symbols;
	TSet<int32> GetRandomSymbolSet(int32 Length = 3);
};
