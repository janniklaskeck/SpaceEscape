// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SEMainGameMode.generated.h"

/**
 *
 */
UCLASS()
class SPACEESCAPE_API ASEMainGameMode : public AGameModeBase
{
	GENERATED_BODY()
protected:
	void BeginPlay() override;
	void Tick(float DeltaTime) override;
	FString InitNewPlayer(APlayerController* NewPlayerController, const FUniqueNetIdRepl& UniqueId, const FString& Options, const FString& Portal = TEXT("")) override;
	void PostLogin(APlayerController* PlayerController) override;
	void Init();

public:
	class ASEPrisonGenerator* GetPrisonGenerator() const
	{
		return PrisonGenerator;
	}
private:
	bool bIsInitialized = false;
	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<class ACharacter> PlayerCharacterClass;
	UPROPERTY()
		class ASEPrisonGenerator* PrisonGenerator;
	UPROPERTY()
		APlayerController* PrisonerPlayerController;
	UPROPERTY()
		class ASEPlayerCharacter* PrisonerCharacter;
	UPROPERTY()
		class ASEPlayerCharacter* HackerCharacter;
	UPROPERTY()
		APlayerController* HackerPlayerController;

	void SpawnHacker(APlayerController* PlayerController);
	void SpawnPrisoner(APlayerController* PlayerController);
};
