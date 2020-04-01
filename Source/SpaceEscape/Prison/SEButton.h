// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SEInteractable.h"
#include "SEButton.generated.h"

UCLASS()
class SPACEESCAPE_API ASEButton : public AActor, public ISEInteractable
{
	GENERATED_BODY()
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class UStaticMeshComponent* ButtonMesh;
public:
	ASEButton();
protected:
	void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere)
		class ASEPrisonCell* Door; // DEBUG
	virtual void Interact() override;
	virtual bool CanInteract() const override;
};
