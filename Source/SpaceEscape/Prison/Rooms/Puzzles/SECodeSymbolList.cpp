// Fill out your copyright notice in the Description page of Project Settings.

#include "SECodeSymbolList.h"

TSet<int32> USECodeSymbolList::GetRandomSymbolSet(int32 Length /*= 3*/)
{
	TSet<int32> SymbolSet;
	TArray<int32> PossibleCodeIndicies;
	for (int32 Index = 0; Index < Symbols.Num(); Index++)
	{
		PossibleCodeIndicies.Add(Index);
	}
	for (int32 Index = 0; Index < FMath::Min(Length, Symbols.Num()); Index++)
	{
		int32 RandomIndex = FMath::RandRange(0, PossibleCodeIndicies.Num() - 1);
		SymbolSet.Add(PossibleCodeIndicies[RandomIndex]);
		PossibleCodeIndicies.RemoveAt(RandomIndex);
	}
	return SymbolSet;
}
