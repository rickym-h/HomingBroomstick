// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/ProjectileManagerSubsystem.h"

#include "Kismet/GameplayStatics.h"
#include "Projectiles/HomingProjectile.h"

AHomingProjectile* UProjectileManagerSubsystem::SpawnProjectile(
	const FTransform& ProjectileTransform, const float ProjectileSpeed, const TSubclassOf<AHomingProjectile>& ProjectileClass) const
{
	AHomingProjectile* Projectile = GetWorld()->SpawnActorDeferred<AHomingProjectile>(ProjectileClass, ProjectileTransform);

	UGameplayStatics::FinishSpawningActor(Projectile, ProjectileTransform);

	UE_LOG(LogTemp, Warning, TEXT("UProjectileManagerSubsystem::SpawnProjectile Called!"));

	return Projectile;
}
