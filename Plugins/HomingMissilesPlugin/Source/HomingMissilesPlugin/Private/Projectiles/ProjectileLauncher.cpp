// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectiles/ProjectileLauncher.h"

#include "Core/ProjectileManagerSubsystem.h"
#include "Projectiles/HomingProjectile.h"


// Sets default values
AProjectileLauncher::AProjectileLauncher()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	SetRootComponent(BaseMesh);

	ProjectileLaunchPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Projectile Launch Point"));
	ProjectileLaunchPoint->SetupAttachment(BaseMesh);
}

void AProjectileLauncher::LaunchProjectile(AActor* Target)
{
	const UWorld* World = GetWorld();
	if (!World)
	{
		UE_LOG(LogTemp, Error, TEXT("AProjectileLauncher::LaunchProjectile - World is null"));
		return;
	}
	
	const UProjectileManagerSubsystem* ProjectileManager = World->GetSubsystem<UProjectileManagerSubsystem>();
	if (!ProjectileManager)
	{
		UE_LOG(LogTemp, Error, TEXT("AProjectileLauncher::LaunchProjectile - ProjectileManager is null"));
		return;
	}

	if (!ProjectileClass)
	{
		UE_LOG(LogTemp, Error, TEXT("AProjectileLauncher::LaunchProjectile - Projectile is null"));
		return;
	}

	if (!Target)
	{
		UE_LOG(LogTemp, Error, TEXT("AProjectileLauncher::LaunchProjectile - Target is null"));
		return;
	}

	ProjectileManager->SpawnProjectile(
		FTransform(FRotator::ZeroRotator, ProjectileLaunchPoint->GetComponentLocation(), FVector(1)),
		1200.f,
		ProjectileClass,
		Target
		);
}

// Called when the game starts or when spawned
void AProjectileLauncher::BeginPlay()
{
	Super::BeginPlay();
	
}
