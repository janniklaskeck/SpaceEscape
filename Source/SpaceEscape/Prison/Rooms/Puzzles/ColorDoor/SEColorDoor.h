// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Prison/Rooms/Puzzles/SEPuzzleBase.h"
#include "SEColorDoor.generated.h"

USTRUCT(BlueprintType)
struct FColorCodeSolution
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadOnly)
		TArray<int32> SolutionColorIndices;
	UPROPERTY(BlueprintReadOnly)
		int32 SymbolIndex = 0;
	UPROPERTY(BlueprintReadOnly)
		bool bIsCorrectSolution = false;
};

UCLASS()
class SPACEESCAPE_API ASEColorDoor : public ASEPuzzleBase
{
	GENERATED_BODY()
public:
	ASEColorDoor();
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class UStaticMeshComponent* FirstDoorPart;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class UStaticMeshComponent* SecondDoorPart;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class UStaticMeshComponent* ThirdDoorPart;
	UPROPERTY(EditDefaultsOnly)
		class USEDoorColors* Colors;
	UPROPERTY(EditDefaultsOnly)
		class USECodeSymbolList* SymbolList;

	void BeginPlay() override;

	UPROPERTY()
		class UMaterialInstanceDynamic* FirstDoorPartMaterialInstance;
	UPROPERTY()
		class UMaterialInstanceDynamic* SecondDoorPartMaterialInstance;
	UPROPERTY()
		class UMaterialInstanceDynamic* ThirdDoorPartMaterialInstance;
	UFUNCTION(NetMulticast, Reliable, WithValidation)
		void MultiCast_UpdateMaterials(int32 Step);
	UPROPERTY(Replicated)
		TArray<int32> FirstPartColorIndices;
	UPROPERTY(Replicated)
		TArray<int32> SecondPartColorIndices;
	UPROPERTY(Replicated)
		int32 ThirdPartColorIndex;

	UPROPERTY(Replicated)
		TArray<FColorCodeSolution> FirstPartSolutions;
	UPROPERTY(Replicated)
		TArray<FColorCodeSolution> SecondPartSolutions;
	UPROPERTY(Replicated)
		TArray<FColorCodeSolution> ThirdPartSolutions;
	UFUNCTION(BlueprintCallable, BlueprintPure)
		TArray<FColorCodeSolution> GetFirstPartSolutions() const
	{
		return FirstPartSolutions;
	}
	UFUNCTION(BlueprintCallable, BlueprintPure)
		TArray<FColorCodeSolution> GetSecondPartSolutions() const
	{
		return SecondPartSolutions;
	}
	UFUNCTION(BlueprintCallable, BlueprintPure)
		TArray<FColorCodeSolution> GetThirdPartSolutions() const
	{
		return ThirdPartSolutions;
	}

	UFUNCTION(BlueprintCallable, BlueprintPure)
		FColorCodeSolution GetFirstPartCorrectSolution() const;
	UFUNCTION(BlueprintCallable, BlueprintPure)
		FColorCodeSolution GetSecondPartCorrectSolution() const;
	UFUNCTION(BlueprintCallable, BlueprintPure)
		FColorCodeSolution GetThirdPartCorrectSolution() const;
	void InitSolutions();
	void InitColors();
	bool IsSameColorCombination(TArray<int32>& First, TArray<int32>& Second);
	UPROPERTY(Replicated, BlueprintReadOnly)
		int32 OpenedBars = 0;
public:
	void InitPuzzle() override;

	void HackPuzzle() override;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
		void OpenFirstPart();
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
		void OpenSecondPart();
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
		void OpenThirdPart();

	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
