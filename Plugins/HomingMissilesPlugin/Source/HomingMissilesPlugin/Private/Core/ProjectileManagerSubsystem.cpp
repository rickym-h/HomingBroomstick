// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/ProjectileManagerSubsystem.h"

#include "Kismet/GameplayStatics.h"
#include "Projectiles/HomingProjectile.h"

AHomingProjectile* UProjectileManagerSubsystem::SpawnHomingProjectile(const FTransform& ProjectileTransform, const float ProjectileSpeed,
	const TSubclassOf<AHomingProjectile>& ProjectileClass, AActor* TargetActor, USoundWave* LaunchSound, USoundWave* OnHitSound) const
{
	if (!ProjectileClass)
	{
		UE_LOG(LogTemp, Error, TEXT("UProjectileManagerSubsystem::SpawnHomingProjectile - ProjectileClass is null"));
		return nullptr;
	}

	// Spawn actor deferred because we need to set properties before allowing its BeginPlay() to be called.
	AHomingProjectile* Projectile = GetWorld()->SpawnActorDeferred<AHomingProjectile>(ProjectileClass, ProjectileTransform);

	const TWeakObjectPtr ActorPointer = TargetActor;
	if (!ActorPointer.IsValid())
	{
		UE_LOG(LogTemp, Error, TEXT("UProjectileManagerSubsystem::SpawnHomingProjectile - TargetActor is invalid"));
		return nullptr;
	}

	// Set the projectile's properties before finishing spawning
	Projectile->InitHomingProjectile(ProjectileSpeed, ActorPointer, OnHitSound);
	UGameplayStatics::FinishSpawningActor(Projectile, ProjectileTransform);

	if (LaunchSound)
	{
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), LaunchSound, Projectile->GetActorLocation());
	}
	
	return Projectile;
}

