// Fill out your copyright notice in the Description page of Project Settings.

#include "SEPlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/WidgetInteractionComponent.h"
#include "SEInteractable.h"

ASEPlayerCharacter::ASEPlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	FirstPersonCamera = CreateDefaultSubobject<UCameraComponent>("FirstPersonCamera");
	FirstPersonCamera->SetupAttachment(RootComponent);

	WidgetInteraction = CreateDefaultSubobject<UWidgetInteractionComponent>("WidgetInteraction");
	WidgetInteraction->SetupAttachment(FirstPersonCamera);
}

void ASEPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void ASEPlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASEPlayerCharacter::Interact_Pressed()
{
	UWorld* World = GetWorld();

	FVector Start = FirstPersonCamera->GetComponentLocation();
	FVector End = Start + FirstPersonCamera->GetForwardVector() * InteractionRange;
	FHitResult Hit;
	if (World->LineTraceSingleByChannel(Hit, Start, End, ECollisionChannel::ECC_Visibility))
	{
		ISEInteractable* InteractableActor = Cast<ISEInteractable>(Hit.Actor.Get());
		if (InteractableActor && InteractableActor->CanInteract())
		{
			UE_LOG(LogTemp, Warning, TEXT("Interact with %s"), *Hit.Actor.Get()->GetName());
			Server_Interact(Hit.Actor.Get());
		}
	}
	WidgetInteraction->PressPointerKey(EKeys::LeftMouseButton);
}

void ASEPlayerCharacter::Interact_Released()
{
	WidgetInteraction->ReleasePointerKey(EKeys::LeftMouseButton);
}

void ASEPlayerCharacter::Server_Interact_Implementation(AActor* Interactable)
{
	ISEInteractable* InteractableActor = Cast<ISEInteractable>(Interactable);
	if (InteractableActor)
		InteractableActor->Interact();
}

bool ASEPlayerCharacter::Server_Interact_Validate(AActor* Interactable)
{
	return true;
}

void ASEPlayerCharacter::MoveForward(float Value)
{
	if (Value != 0.0f)
	{
		AddMovementInput(GetActorForwardVector(), Value);
	}
}

void ASEPlayerCharacter::MoveRight(float Value)
{
	if (Value != 0.0f)
	{
		AddMovementInput(GetActorRightVector(), Value);
	}
}
