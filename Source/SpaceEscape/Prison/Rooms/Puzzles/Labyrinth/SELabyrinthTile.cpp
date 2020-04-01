// Fill out your copyright notice in the Description page of Project Settings.

#include "SELabyrinthTile.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Components/SceneComponent.h"
#include "Net/UnrealNetwork.h"
#include "SEPlayerCharacter.h"

ASELabyrinthTile::ASELabyrinthTile()
{
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>("RootComponent");
	RootComponent = Root;

	TileMesh = CreateDefaultSubobject<UStaticMeshComponent>("TileMesh");
	TileMesh->SetupAttachment(RootComponent);

	StepTriggerBox = CreateDefaultSubobject<UBoxComponent>("StepTrigger");
	StepTriggerBox->SetupAttachment(RootComponent);
}

void ASELabyrinthTile::BeginPlay()
{
	Super::BeginPlay();
	if (UndiscoveredMaterial)
		UndiscoveredMaterialInstance = UMaterialInstanceDynamic::Create(UndiscoveredMaterial, this);
	if (CorrectMaterial)
		CorrectMaterialInstance = UMaterialInstanceDynamic::Create(CorrectMaterial, this);
	if (WrongMaterial)
		WrongMaterialInstance = UMaterialInstanceDynamic::Create(WrongMaterial, this);
}

void ASELabyrinthTile::Init(int32 NewXPos, int32 NewYPos)
{
	Position.XPos = NewXPos;
	Position.YPos = NewYPos;
	PublicState = ESELabyrinthTileState::Undiscovered;
	StepTriggerBox->OnComponentBeginOverlap.AddDynamic(this, &ASELabyrinthTile::OnTileOverlap);
}

void ASELabyrinthTile::SetPrivateState(ESELabyrinthTileState State)
{
	PrivateState = State;
}

void ASELabyrinthTile::SwitchState_Implementation()
{
	PublicState = PrivateState;
	switch (PublicState)
	{
	case ESELabyrinthTileState::Undiscovered:
		TileMesh->SetMaterial(1, UndiscoveredMaterialInstance);
		break;
	case ESELabyrinthTileState::Correct:
		TileMesh->SetMaterial(1, CorrectMaterialInstance);
		break;
	case ESELabyrinthTileState::Wrong:
		TileMesh->SetMaterial(1, WrongMaterialInstance);
		break;
	default:
		break;
	}
}
bool ASELabyrinthTile::SwitchState_Validate()
{
	return true;
}

void ASELabyrinthTile::OnTileOverlap(class UPrimitiveComponent* OverlappedComponent, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (Cast<ASEPlayerCharacter>(OtherActor))
		SwitchState();
}

void ASELabyrinthTile::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ASELabyrinthTile, Position);
	DOREPLIFETIME(ASELabyrinthTile, PublicState);
	DOREPLIFETIME(ASELabyrinthTile, PrivateState);
}
