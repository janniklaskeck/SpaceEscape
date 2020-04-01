// Fill out your copyright notice in the Description page of Project Settings.

#include "SEMainGameMode.h"
#include "SEPlayerStart.h"
#include "SEPlayerController.h"
#include "EngineUtils.h"
#include "SEGameState.h"
#include "Kismet/GameplayStatics.h"
#include "SEPrisonGenerator.h"
#include "SEPrisonCell.h"
#include "SEPlayerCharacter.h"
#include "SESpaceShip.h"

void ASEMainGameMode::BeginPlay()
{
	Super::BeginPlay();

}

void ASEMainGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	ASEGameState* SEGameState = GetGameState<ASEGameState>();
	if (SEGameState->EscapeCountdown > 0)
	{
		SEGameState->EscapeCountdown -= DeltaTime;
	}
	else
	{
		// GameOver
	}
}

FString ASEMainGameMode::InitNewPlayer(APlayerController* NewPlayerController, const FUniqueNetIdRepl& UniqueId, const FString& Options, const FString& Portal /*= TEXT("")*/)
{

	FString Result = Super::InitNewPlayer(NewPlayerController, UniqueId, Options, Portal);
	return Result;
}

void ASEMainGameMode::PostLogin(APlayerController* PlayerController)
{
	Super::PostLogin(PlayerController);
	if (!PrisonerPlayerController)
	{
		PrisonerPlayerController = PlayerController;
	}
	else
	{
		HackerPlayerController = PlayerController;
	}
	if (PrisonerPlayerController && HackerPlayerController)
	{
		// Delay init to allow world loading on clients. Should be replaced if possible
		FTimerHandle TempHandle;
		GetWorld()->GetTimerManager().SetTimer(TempHandle, this, &ASEMainGameMode::Init, 1.f, false, 1.5f);
	}
}

void ASEMainGameMode::Init()
{
	if (!bIsInitialized)
	{
		bIsInitialized = true;
		TArray<AActor*> Generators;
		UGameplayStatics::GetAllActorsOfClass(this, ASEPrisonGenerator::StaticClass(), Generators);
		if (Generators.Num() > 0)
		{
			PrisonGenerator = Cast<ASEPrisonGenerator>(Generators[0]);
			PrisonGenerator->BuildPrison();
		}
		SpawnHacker(HackerPlayerController);
		SpawnPrisoner(PrisonerPlayerController);
	}
}

void ASEMainGameMode::SpawnHacker(APlayerController* PlayerController)
{
	TArray<AActor*> Spaceships;
	UGameplayStatics::GetAllActorsOfClass(this, ASESpaceShip::StaticClass(), Spaceships);
	if (Spaceships.Num() > 0)
	{
		ASESpaceShip* Spaceship = Cast<ASESpaceShip>(Spaceships[0]);
		HackerCharacter = GetWorld()->SpawnActor<ASEPlayerCharacter>(PlayerCharacterClass, Spaceship->GetSpawnLocation()->GetComponentTransform());
		PlayerController->Possess(HackerCharacter);
	}
}

void ASEMainGameMode::SpawnPrisoner(APlayerController* PlayerController)
{
	if (PrisonGenerator)
	{
		PrisonerCharacter = GetWorld()->SpawnActor<ASEPlayerCharacter>(PlayerCharacterClass, PrisonGenerator->GetPrisonCellRoom()->GetSpawnLocation()->GetComponentTransform());
		PlayerController->Possess(PrisonerCharacter);
	}
}
