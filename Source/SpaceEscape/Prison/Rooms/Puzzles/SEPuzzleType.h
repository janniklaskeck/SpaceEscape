// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class ESEPuzzleType : uint8
{
	NONE,
	Door_Color,
	Door_Balance,
	Door_Code,
	Door_Keycard,
	Room_Camera,
	Room_Laser,
	Room_Labyrinth
};