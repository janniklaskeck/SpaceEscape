// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SEHackerConsole.generated.h"

UCLASS()
class SPACEESCAPE_API ASEHackerConsole : public AActor
{
	GENERATED_BODY()
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class USceneComponent* Root;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class UWidgetComponent* ConsoleWidget;
public:
	ASEHackerConsole();

protected:
	void BeginPlay() override;
	void Tick(float DeltaTime) override;

};
