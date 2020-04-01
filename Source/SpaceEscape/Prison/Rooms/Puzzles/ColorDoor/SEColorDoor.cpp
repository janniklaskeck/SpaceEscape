// Fill out your copyright notice in the Description page of Project Settings.

#include "SEColorDoor.h"
#include "Components/StaticMeshComponent.h"
#include "Materials/Material.h"
#include "SEDoorColors.h"
#include "Net/UnrealNetwork.h"
#include "SECodeSymbolList.h"
#include "SEUtility.h"

ASEColorDoor::ASEColorDoor()
{
	FirstDoorPart = CreateDefaultSubobject<UStaticMeshComponent>("FirstDoorPart");
	FirstDoorPart->SetupAttachment(RootComponent);

	SecondDoorPart = CreateDefaultSubobject<UStaticMeshComponent>("SecondDoorPart");
	SecondDoorPart->SetupAttachment(RootComponent);

	ThirdDoorPart = CreateDefaultSubobject<UStaticMeshComponent>("ThirdDoorPart");
	ThirdDoorPart->SetupAttachment(RootComponent);
}

void ASEColorDoor::BeginPlay()
{
	Super::BeginPlay();
	UMaterialInterface* BaseMaterial = FirstDoorPart->GetMaterial(0);
	FirstDoorPartMaterialInstance = UMaterialInstanceDynamic::Create(BaseMaterial, this);
	FirstDoorPart->SetMaterial(0, FirstDoorPartMaterialInstance);

	SecondDoorPartMaterialInstance = UMaterialInstanceDynamic::Create(BaseMaterial, this);
	SecondDoorPart->SetMaterial(0, SecondDoorPartMaterialInstance);

	ThirdDoorPartMaterialInstance = UMaterialInstanceDynamic::Create(BaseMaterial, this);
	ThirdDoorPart->SetMaterial(0, ThirdDoorPartMaterialInstance);
}

FColorCodeSolution ASEColorDoor::GetFirstPartCorrectSolution() const
{
	for (FColorCodeSolution Solution : FirstPartSolutions)
	{
		if (Solution.bIsCorrectSolution)
			return Solution;
	}
	return FColorCodeSolution();
}

FColorCodeSolution ASEColorDoor::GetSecondPartCorrectSolution() const
{
	for (FColorCodeSolution Solution : SecondPartSolutions)
	{
		if (Solution.bIsCorrectSolution)
			return Solution;
	}
	return FColorCodeSolution();
}

FColorCodeSolution ASEColorDoor::GetThirdPartCorrectSolution() const
{
	for (FColorCodeSolution Solution : ThirdPartSolutions)
	{
		if (Solution.bIsCorrectSolution)
			return Solution;
	}
	return FColorCodeSolution();
}

void ASEColorDoor::InitSolutions()
{
	for (int32 Index = 0; Index < 10; Index++)
	{
		TArray<int32> Exceptions;
		for (int32 SolutionIndex = 0; SolutionIndex < FirstPartSolutions.Num(); SolutionIndex++)
		{
			Exceptions.Add(FirstPartSolutions[SolutionIndex].SymbolIndex);
		}
		FColorCodeSolution Solution;
		Solution.SymbolIndex = USEUtility::GetRandRangeWithout(0, SymbolList->Symbols.Num() - 1, Exceptions);
		Solution.SolutionColorIndices.Append(Colors->FirstPartCombinations[Index].AsArray());
		Solution.bIsCorrectSolution = IsSameColorCombination(Solution.SolutionColorIndices, FirstPartColorIndices);
		USEUtility::ShuffleArray<int32>(Solution.SolutionColorIndices);
		FirstPartSolutions.Add(Solution);
	}
	USEUtility::ShuffleArray<FColorCodeSolution>(FirstPartSolutions);

	for (int32 Index = 0; Index < 10; Index++)
	{
		TArray<int32> Exceptions;
		for (int32 SolutionIndex = 0; SolutionIndex < SecondPartSolutions.Num(); SolutionIndex++)
		{
			Exceptions.Add(SecondPartSolutions[SolutionIndex].SymbolIndex);
		}
		FColorCodeSolution Solution;
		Solution.SymbolIndex = USEUtility::GetRandRangeWithout(0, SymbolList->Symbols.Num() - 1, Exceptions);
		Solution.SolutionColorIndices.Add(Colors->SecondPartCombinations[Index].First);
		Solution.SolutionColorIndices.Add(Colors->SecondPartCombinations[Index].Second);
		Solution.bIsCorrectSolution = IsSameColorCombination(Solution.SolutionColorIndices, SecondPartColorIndices);
		USEUtility::ShuffleArray<int32>(Solution.SolutionColorIndices);
		SecondPartSolutions.Add(Solution);
	}
	USEUtility::ShuffleArray<FColorCodeSolution>(SecondPartSolutions);

	for (int32 Index = 0; Index < 5; Index++)
	{
		TArray<int32> Exceptions;
		for (int32 SolutionIndex = 0; SolutionIndex < ThirdPartSolutions.Num(); SolutionIndex++)
		{
			Exceptions.Add(ThirdPartSolutions[SolutionIndex].SymbolIndex);
		}
		FColorCodeSolution Solution;
		Solution.SymbolIndex = USEUtility::GetRandRangeWithout(0, SymbolList->Symbols.Num() - 1, Exceptions);
		Solution.SolutionColorIndices.Add(Index);
		Solution.bIsCorrectSolution = Solution.SolutionColorIndices[0] == ThirdPartColorIndex;
		USEUtility::ShuffleArray<int32>(Solution.SolutionColorIndices);
		ThirdPartSolutions.Add(Solution);
	}
	USEUtility::ShuffleArray<FColorCodeSolution>(ThirdPartSolutions);
}

void ASEColorDoor::InitColors()
{
	TArray<int32> RandomColors;
	for (int32 Index = 0; Index < Colors->Colors.Num(); Index++)
	{
		RandomColors.Add(Index);
	}
	for (int32 Index = 0; Index < 3; Index++)
	{
		int32 RandomIndex = FMath::RandRange(0, RandomColors.Num() - 1);
		FirstPartColorIndices.Add(RandomColors[RandomIndex]);
		RandomColors.RemoveAt(RandomIndex);
	}

	RandomColors.Reset(5);
	for (int32 Index = 0; Index < Colors->Colors.Num(); Index++)
	{
		RandomColors.Add(Index);
	}
	for (int32 Index = 0; Index < 2; Index++)
	{
		int32 RandomIndex = FMath::RandRange(0, RandomColors.Num() - 1);
		SecondPartColorIndices.Add(RandomColors[RandomIndex]);
		RandomColors.RemoveAt(RandomIndex);
	}

	ThirdPartColorIndex = FMath::RandRange(0, Colors->Colors.Num() - 1);
}

bool ASEColorDoor::IsSameColorCombination(TArray<int32>& First, TArray<int32>& Second)
{
	if (First.Num() < Second.Num())
	{
		return false;
	}
	TArray<int32> SecondCopy(Second);
	for (int32 Index = 0; Index < Second.Num(); Index++)
	{
		SecondCopy.RemoveSingle(First[Index]);
	}
	return SecondCopy.Num() == 0;
}

void ASEColorDoor::MultiCast_UpdateMaterials_Implementation(int32 Step)
{
	int32 SecondColorIndex = 0;
	int32 ThirdColorIndex = 0;
	if (Step == 0)
	{
		SecondColorIndex = FirstPartColorIndices[1];
		ThirdColorIndex = FirstPartColorIndices[2];
	}
	else if (Step == 1)
	{
		SecondColorIndex = SecondPartColorIndices[0];
		ThirdColorIndex = SecondPartColorIndices[1];
	}
	else
	{
		ThirdColorIndex = ThirdPartColorIndex;
	}
	FirstDoorPartMaterialInstance->SetVectorParameterValue("Color", Colors->Colors[FirstPartColorIndices[0]]);
	SecondDoorPartMaterialInstance->SetVectorParameterValue("Color", Colors->Colors[SecondColorIndex]);
	ThirdDoorPartMaterialInstance->SetVectorParameterValue("Color", Colors->Colors[ThirdColorIndex]);
}

bool ASEColorDoor::MultiCast_UpdateMaterials_Validate(int32 Step)
{
	return true;
}

void ASEColorDoor::InitPuzzle()
{
	InitColors();
	InitSolutions();
	MultiCast_UpdateMaterials(0);
}

void ASEColorDoor::HackPuzzle()
{
	switch (OpenedBars)
	{
	case 0:
		OpenFirstPart();
		break;
	case 1:
		OpenSecondPart();
		break;
	case 2:
		OpenThirdPart();
		break;
	default:
		break;
	}
	++OpenedBars;
	MultiCast_UpdateMaterials(OpenedBars);
}

void ASEColorDoor::OpenFirstPart_Implementation()
{

}

void ASEColorDoor::OpenSecondPart_Implementation()
{

}

void ASEColorDoor::OpenThirdPart_Implementation()
{

}

void ASEColorDoor::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ASEColorDoor, FirstPartColorIndices);
	DOREPLIFETIME(ASEColorDoor, SecondPartColorIndices);
	DOREPLIFETIME(ASEColorDoor, ThirdPartColorIndex);
	DOREPLIFETIME(ASEColorDoor, FirstPartSolutions);
	DOREPLIFETIME(ASEColorDoor, SecondPartSolutions);
	DOREPLIFETIME(ASEColorDoor, ThirdPartSolutions);
	DOREPLIFETIME(ASEColorDoor, OpenedBars);
}
