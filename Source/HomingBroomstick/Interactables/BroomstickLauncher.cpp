// Fill out your copyright notice in the Description page of Project Settings.


#include "BroomstickLauncher.h"

#include "Bats/FlyingBat.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
ABroomstickLauncher::ABroomstickLauncher()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

void ABroomstickLauncher::Interact_Implementation(AActor* Interactor)
{
	UE_LOG(LogTemp, Warning, TEXT("%s interacted with %s"), *Interactor->GetName(), *GetName());


	// This is an expensive function, in a real game ideally pointers to the bats would be stored somewhere to be found quickly. For the demo I have just used this for simplicity.
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AFlyingBat::StaticClass(), FoundActors);

	if (FoundActors.Num() == 0)
	{
		LaunchProjectile(nullptr);
	} else
	{
		LaunchProjectile(FoundActors[FMath::RandRange(0, FoundActors.Num() - 1)]);
	}
}

// Called when the game starts or when spawned
void ABroomstickLauncher::BeginPlay()
{
	Super::BeginPlay();
	
}
