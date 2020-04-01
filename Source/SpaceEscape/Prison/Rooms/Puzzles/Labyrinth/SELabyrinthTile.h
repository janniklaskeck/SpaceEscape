// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SELabyrinthTile.generated.h"

UENUM()
enum class ESELabyrinthTileState : uint8
{
	Undiscovered,
	Correct,
	Wrong
};

USTRUCT(BlueprintType)
struct FTilePosition
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadOnly)
		int32 XPos;
	UPROPERTY(BlueprintReadOnly)
		int32 YPos;
};

UCLASS()
class SPACEESCAPE_API ASELabyrinthTile : public AActor
{
	GENERATED_BODY()
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class USceneComponent* Root;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class UBoxComponent* StepTriggerBox;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class UStaticMeshComponent* TileMesh;
public:
	ASELabyrinthTile();
	void BeginPlay() override;
	void Init(int32 NewXPos, int32 NewYPos);

	void SetPrivateState(ESELabyrinthTileState State);

	UFUNCTION(NetMulticast, Reliable, WithValidation)
		void SwitchState();

	UFUNCTION(BlueprintCallable, BlueprintPure)
		FTilePosition GetPosition() const
	{
		return Position;
	}
	UFUNCTION(BlueprintCallable, BlueprintPure)
		bool IsCorrectTile() const
	{
		return PrivateState == ESELabyrinthTileState::Correct;
	}
private:
	UPROPERTY(Replicated)
		FTilePosition Position;

	UPROPERTY(Replicated)
		ESELabyrinthTileState PublicState = ESELabyrinthTileState::Undiscovered;
	UPROPERTY(Replicated)
		ESELabyrinthTileState PrivateState = ESELabyrinthTileState::Undiscovered;

	UPROPERTY(EditDefaultsOnly)
		class UMaterialInterface* UndiscoveredMaterial;
	UPROPERTY(EditDefaultsOnly)
		class UMaterialInterface* CorrectMaterial;
	UPROPERTY(EditDefaultsOnly)
		class UMaterialInterface* WrongMaterial;
	UPROPERTY()
		class UMaterialInstanceDynamic* UndiscoveredMaterialInstance;
	UPROPERTY()
		class UMaterialInstanceDynamic* CorrectMaterialInstance;
	UPROPERTY()
		class UMaterialInstanceDynamic* WrongMaterialInstance;

	UFUNCTION()
		void OnTileOverlap(class UPrimitiveComponent* OverlappedComponent, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const;
};
