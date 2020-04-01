// Fill out your copyright notice in the Description page of Project Settings.

#include "SEButton.h"
#include "Components/StaticMeshComponent.h"
#include "SEPrisonCell.h"
#include "SEMainGameMode.h"
#include "SEPrisonGenerator.h"
#include "SEUtility.h"

ASEButton::ASEButton()
{
	PrimaryActorTick.bCanEverTick = false;

	ButtonMesh = CreateDefaultSubobject<UStaticMeshComponent>("ButtonMesh");
	RootComponent = ButtonMesh;
}

void ASEButton::BeginPlay()
{
	Super::BeginPlay();
}

void ASEButton::Interact()
{
}

bool ASEButton::CanInteract() const
{
	return true;
}

