// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "SEUtility.generated.h"

/**
 *
 */
UCLASS()
class SPACEESCAPE_API USEUtility : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:

	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (WorldContext = "WorldContextObject"))
		static class ASEMainGameMode* GetSEMainGameMode(UObject* WorldContextObject);

	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (WorldContext = "WorldContextObject"))
		static class USEGameInstance* GetSEGameInstance(UObject* WorldContextObject);

	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (WorldContext = "WorldContextObject"))
		static class ASEGameState* GetSEGameState(UObject* WorldContextObject);

	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (WorldContext = "WorldContextObject"))
		static class ASEPlayerController* GetLocalSEPlayerController(UObject* WorldContextObject);

	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (WorldContext = "WorldContextObject"))
		static class ASEPrisonGenerator* GetPrisonGenerator(UObject* WorldContextObject);

	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (WorldContext = "WorldContextObject"))
		static class ASERoomBase* GetRoomWithCode(UObject* WorldContextObject, TArray<int32> Code);

	UFUNCTION(BlueprintCallable, BlueprintPure)
		static int32 GetRandRangeWithout(int32 Min, int32 Max, TArray<int32> Exceptions);

	template<typename T>
	static FORCEINLINE void ShuffleArray(TArray<T>& Array);
};

template<typename T>
void USEUtility::ShuffleArray(TArray<T>& Array)
{
	for (int32 Index = Array.Num() - 1; Index > 0; Index--)
	{
		int32 RandomIndex = FMath::RandRange(0, Index);
		Array.Swap(Index, RandomIndex);
	}
}
