// Fill out your copyright notice in the Description page of Project Settings.

#include "SEHackerConsole.h"
#include "Components/SceneComponent.h"
#include "Components/WidgetComponent.h"

ASEHackerConsole::ASEHackerConsole()
{
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>("RootComponent");
	RootComponent = Root;

	ConsoleWidget = CreateDefaultSubobject<UWidgetComponent>("ConsoleWidget");
	ConsoleWidget->SetupAttachment(RootComponent);
}

void ASEHackerConsole::BeginPlay()
{
	Super::BeginPlay();

}

void ASEHackerConsole::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
