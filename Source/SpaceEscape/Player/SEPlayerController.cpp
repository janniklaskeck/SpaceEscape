// Fill out your copyright notice in the Description page of Project Settings.

#include "SEPlayerController.h"
#include "SEPlayerCharacter.h"
#include "SEPuzzleBase.h"

ASEPlayerController::ASEPlayerController()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ASEPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	InputComponent->BindAction("Interact", IE_Pressed, this, &ASEPlayerController::InteractPressed);
	InputComponent->BindAction("Interact", IE_Released, this, &ASEPlayerController::InteractReleased);
	InputComponent->BindAction("PauseGame", IE_Pressed, this, &ASEPlayerController::PausePressed).bExecuteWhenPaused = true;

	InputComponent->BindAxis("MoveForward", this, &ASEPlayerController::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &ASEPlayerController::MoveRight);

	InputComponent->BindAxis("Turn", this, &ASEPlayerController::TurnYaw);
	InputComponent->BindAxis("LookUp", this, &ASEPlayerController::TurnPitch);
}

void ASEPlayerController::InteractPressed()
{
	if (GetPawn())
		GetPlayerPawn()->Interact_Pressed();
}

void ASEPlayerController::InteractReleased()
{
	if (GetPawn())
		GetPlayerPawn()->Interact_Released();
}

void ASEPlayerController::PausePressed()
{

}

void ASEPlayerController::MoveForward(float Value)
{
	if (GetPawn())
		GetPlayerPawn()->MoveForward(Value);
}

void ASEPlayerController::MoveRight(float Value)
{
	if (GetPawn())
		GetPlayerPawn()->MoveRight(Value);
}

void ASEPlayerController::TurnYaw(float Value)
{
	AddYawInput(Value);
}

void ASEPlayerController::TurnPitch(float Value)
{
	AddPitchInput(Value);
}

void ASEPlayerController::HackPuzzle_Implementation(class ASEPuzzleBase* Puzzle)
{
	if (Puzzle)
	{
		Puzzle->HackPuzzle();
	}
}

bool ASEPlayerController::HackPuzzle_Validate(class ASEPuzzleBase* Puzzle)
{
	return true;
}

class ASEPlayerCharacter* ASEPlayerController::GetPlayerPawn() const
{
	return Cast<ASEPlayerCharacter>(GetPawn());
}

bool ASEPlayerController::IsPrisoner() const
{
	return bIsPrisoner;
}
