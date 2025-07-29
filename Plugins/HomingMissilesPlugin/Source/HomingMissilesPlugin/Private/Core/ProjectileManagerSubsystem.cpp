// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/ProjectileManagerSubsystem.h"

#include "Kismet/GameplayStatics.h"
#include "Projectiles/HomingProjectile.h"

AHomingProjectile* UProjectileManagerSubsystem::SpawnProjectile(const FTransform& ProjectileTransform, const float ProjectileSpeed, const TSubclassOf<AHomingProjectile>& ProjectileClass, TWeakObjectPtr<AActor> TargetActor) const
{
	if (!ProjectileClass) UE_LOG(LogTemp, Error, TEXT("UProjectileManagerSubsystem::SpawnProjectile - ProjectileClass is null"));
	
	AHomingProjectile* Projectile = GetWorld()->SpawnActorDeferred<AHomingProjectile>(ProjectileClass, ProjectileTransform);
	Projectile->InitHomingProjectile(ProjectileSpeed, TargetActor);
	UGameplayStatics::FinishSpawningActor(Projectile, ProjectileTransform);

	return Projectile;
}
