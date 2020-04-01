// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerStart.h"
#include "SEPlayerStart.generated.h"

/**
 * 
 */
UCLASS()
class SPACEESCAPE_API ASEPlayerStart : public APlayerStart
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere)
		bool bIsPrisonerStart = false;
};
