// Fill out your copyright notice in the Description page of Project Settings.

#include "SERoomBase.h"
#include "Components/SceneComponent.h"
#include "SECodeSymbolList.h"
#include "SEPrisonGenerator.h"
#include "Net/UnrealNetwork.h"

#if WITH_EDITOR
#include "DrawDebugHelpers.h"
#endif

ASERoomBase::ASERoomBase()
{
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>("RootComponent");
	RootComponent = Root;

	EntryLocation = CreateDefaultSubobject<USceneComponent>("EntryLocation");
	EntryLocation->SetupAttachment(RootComponent);

	ExitLeftLocation = CreateDefaultSubobject<USceneComponent>("ExitLeftLocation");
	ExitLeftLocation->SetupAttachment(RootComponent);
	ExitRightLocation = CreateDefaultSubobject<USceneComponent>("ExitRightLocation");
	ExitRightLocation->SetupAttachment(RootComponent);
	ExitForwardLocation = CreateDefaultSubobject<USceneComponent>("ExitForwardLocation");
	ExitForwardLocation->SetupAttachment(RootComponent);
	bReplicates = true;
}

void ASERoomBase::BeginPlay()
{
	Super::BeginPlay();

}

void ASERoomBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
#if WITH_EDITOR
	UWorld* World = GetWorld();
	if (World)
	{
		if (World->WorldType == EWorldType::Editor || World->WorldType == EWorldType::EditorPreview)
		{
			if (bEntryActive)
				DrawDebugSphere(World, EntryLocation->GetComponentLocation(), 10.f, 12, FColor::Green);
			if (bExitForwardActive)
				DrawDebugSphere(World, ExitForwardLocation->GetComponentLocation(), 10.f, 12, FColor::Red);
			if (bExitRightActive)
				DrawDebugSphere(World, ExitRightLocation->GetComponentLocation(), 10.f, 12, FColor::Red);
			if (bExitLeftActive)
				DrawDebugSphere(World, ExitLeftLocation->GetComponentLocation(), 10.f, 12, FColor::Red);
		}
	}
#endif
}

void ASERoomBase::Init()
{
	Code = PrisonGenerator->GenerateUniqueRoomCode(FMath::RandRange(MinCodeLength, MaxCodeLength));
}

bool ASERoomBase::HasSameCode(TArray<int32>& OtherCode)
{
	if (OtherCode.Num() == 0 || OtherCode.Num() != Code.Num())
		return false;
	TArray<int32> OtherCodeCopy(OtherCode);
	for (int32 Number : Code)
	{
		OtherCodeCopy.RemoveSingle(Number);
	}
	return OtherCodeCopy.Num() == 0;
}

FString ASERoomBase::GetRoomCodeAsString() const
{
	FString CodeString;
	for (int32 Number : Code)
	{
		CodeString += FString::FromInt(Number);
	}
	return CodeString;
}

class ASEPuzzleBase* ASERoomBase::GetRoomPuzzle()
{
	return nullptr;
}

void ASERoomBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty> &OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ASERoomBase, Code);
}
