// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SEPuzzleBase.generated.h"

UCLASS()
class SPACEESCAPE_API ASEPuzzleBase : public AActor
{
	GENERATED_BODY()
public:
	ASEPuzzleBase();
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class USceneComponent* Root;
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

public:
	virtual void InitPuzzle();

	UFUNCTION(BlueprintCallable)
		virtual void HackPuzzle();
};
