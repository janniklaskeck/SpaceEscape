// Fill out your copyright notice in the Description page of Project Settings.

#include "SEPuzzleBase.h"
#include "Components/SceneComponent.h"

ASEPuzzleBase::ASEPuzzleBase()
{
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>("RootComponent");
	RootComponent = Root;

	bReplicates = true;
}

void ASEPuzzleBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASEPuzzleBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASEPuzzleBase::InitPuzzle()
{

}

void ASEPuzzleBase::HackPuzzle()
{

}

