// Fill out your copyright notice in the Description page of Project Settings.


#include "BroomstickLauncher.h"


// Sets default values
ABroomstickLauncher::ABroomstickLauncher()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

void ABroomstickLauncher::Interact_Implementation(AActor* Interactor)
{
	UE_LOG(LogTemp, Warning, TEXT("%s interacted with %s"), *Interactor->GetName(), *GetName());
	LaunchProjectile(Interactor);
}

// Called when the game starts or when spawned
void ABroomstickLauncher::BeginPlay()
{
	Super::BeginPlay();
	
}
