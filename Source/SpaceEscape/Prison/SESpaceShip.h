// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SESpaceShip.generated.h"

UCLASS()
class SPACEESCAPE_API ASESpaceShip : public AActor
{
	GENERATED_BODY()
public:
	ASESpaceShip();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class USceneComponent* Root;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class USceneComponent* SpawnLocation;


protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
public:
	class USceneComponent* GetSpawnLocation() const
	{
		return SpawnLocation;
	}
};
