// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "SEGameState.generated.h"

/**
 * 
 */
UCLASS()
class SPACEESCAPE_API ASEGameState : public AGameStateBase
{
	GENERATED_BODY()
public:
	UPROPERTY(Replicated, EditDefaultsOnly)
		float EscapeCountdown = 600.f;
	UFUNCTION(BlueprintCallable, BlueprintPure)
		float GetEscapeCountdown() const;

	UPROPERTY(Replicated)
		int32 CurrentAlarmLevel = 0;
	UFUNCTION(BlueprintCallable, BlueprintPure)
		int32 GetCurrentAlarmLevel() const;
	UPROPERTY(Replicated)
		int32 MaxAlarmLevel = 3;
	UFUNCTION(BlueprintCallable, BlueprintPure)
		int32 GetMaxAlarmLevel() const;

	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty> &OutLifetimeProps) const override;
};
