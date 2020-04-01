// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SEPuzzleType.h"
#include "SERoomBase.generated.h"

UCLASS()
class SPACEESCAPE_API ASERoomBase : public AActor
{
	GENERATED_BODY()
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class USceneComponent* Root;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class USceneComponent* EntryLocation;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class USceneComponent* ExitLeftLocation;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class USceneComponent* ExitRightLocation;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class USceneComponent* ExitForwardLocation;
public:
	ASERoomBase();
protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	virtual bool ShouldTickIfViewportsOnly() const override
	{
		return true;
	}
public:
	virtual void Init();

	class USceneComponent* GetEntry() const
	{
		return EntryLocation;
	}
	class USceneComponent* GetForwardExit() const
	{
		return ExitForwardLocation;
	}
	class USceneComponent* GetRightExit() const
	{
		return ExitRightLocation;
	}
	class USceneComponent* GetLeftExit() const
	{
		return ExitLeftLocation;
	}
	bool HasSameCode(TArray<int32>& OtherCode);
	UFUNCTION(BlueprintCallable, BlueprintPure)
		TArray<int32> GetRoomCode() const
	{
		return Code;
	}
	UFUNCTION(BlueprintCallable, BlueprintPure)
		FString GetRoomCodeAsString() const;
	UFUNCTION(BlueprintCallable, BlueprintPure)
		ESEPuzzleType GetPuzzleType() const
	{
		return PuzzleType;
	}
	UFUNCTION(BlueprintCallable, BlueprintPure)
		virtual class ASEPuzzleBase* GetRoomPuzzle();

public:
	UPROPERTY(EditDefaultsOnly)
		bool bEntryActive = true;
	UPROPERTY(EditDefaultsOnly)
		bool bExitForwardActive = true;
	UPROPERTY(EditDefaultsOnly)
		bool bExitRightActive = false;
	UPROPERTY(EditDefaultsOnly)
		bool bExitLeftActive = false;

	UPROPERTY(EditDefaultsOnly)
		ESEPuzzleType PuzzleType;

	UPROPERTY()
		class ASEPrisonGenerator* PrisonGenerator;

protected:
	UPROPERTY(EditDefaultsOnly)
		int32 MinCodeLength = 2;
	UPROPERTY(EditDefaultsOnly)
		int32 MaxCodeLength = 4;
	UPROPERTY(Replicated)
		TArray<int32> Code;

	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty> &OutLifetimeProps) const override;
};
