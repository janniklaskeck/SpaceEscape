// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "SEPlayerController.generated.h"

/**
 *
 */
UCLASS()
class SPACEESCAPE_API ASEPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	ASEPlayerController();

	void SetupInputComponent() override;

	void InteractPressed();
	void InteractReleased();

	void PausePressed();

	void MoveForward(float Value);
	void MoveRight(float Value);

	void TurnYaw(float Value);
	void TurnPitch(float Value);

	UFUNCTION(Server, Reliable, WithValidation, BlueprintCallable)
		void HackPuzzle(class ASEPuzzleBase* Puzzle);

	UFUNCTION(BlueprintCallable, BlueprintPure)
		class ASEPlayerCharacter* GetPlayerPawn() const;

	UFUNCTION(BlueprintCallable, BlueprintPure)
		bool IsPrisoner() const;
	bool bIsPrisoner;
};
