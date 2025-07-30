// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interfaces/InteractableInterface.h"
#include "Projectiles/ProjectileLauncher.h"
#include "BroomstickLauncher.generated.h"

UCLASS()
class HOMINGBROOMSTICK_API ABroomstickLauncher : public AProjectileLauncher, public IInteractableInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABroomstickLauncher();

	virtual void Interact_Implementation(AActor* Interactor) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
