// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SEPlayerCharacter.generated.h"

UCLASS()
class SPACEESCAPE_API ASEPlayerCharacter : public ACharacter
{
	GENERATED_BODY()
public:
	ASEPlayerCharacter();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* FirstPersonCamera;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class UWidgetInteractionComponent* WidgetInteraction;

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditDefaultsOnly)
		float InteractionRange = 500.f;

public:

	void Interact_Pressed();
	void Interact_Released();
	UFUNCTION(Server, Reliable, WithValidation)
		void Server_Interact(class AActor* Interactable);

	void MoveForward(float Value);
	void MoveRight(float Value);
};
