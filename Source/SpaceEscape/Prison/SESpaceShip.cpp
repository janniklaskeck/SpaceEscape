// Fill out your copyright notice in the Description page of Project Settings.

#include "SESpaceShip.h"

ASESpaceShip::ASESpaceShip()
{
	PrimaryActorTick.bCanEverTick = true;
	
	Root = CreateDefaultSubobject<USceneComponent>("RootComponent");
	RootComponent = Root;

	SpawnLocation = CreateDefaultSubobject<USceneComponent>("SpawnLocation");
	SpawnLocation->SetupAttachment(RootComponent);
}

void ASESpaceShip::BeginPlay()
{
	Super::BeginPlay();

}

void ASESpaceShip::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
