// Fill out your copyright notice in the Description page of Project Settings.

#include "SEGameState.h"
#include "Net/UnrealNetwork.h"

float ASEGameState::GetEscapeCountdown() const
{
	return EscapeCountdown;
}

int32 ASEGameState::GetCurrentAlarmLevel() const
{
	return CurrentAlarmLevel;
}

int32 ASEGameState::GetMaxAlarmLevel() const
{
	return MaxAlarmLevel;
}

void ASEGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty> &OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ASEGameState, EscapeCountdown);
	DOREPLIFETIME(ASEGameState, CurrentAlarmLevel);
	DOREPLIFETIME(ASEGameState, MaxAlarmLevel);
}
