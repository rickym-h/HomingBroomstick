// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/ProjectileManagerSubsystem.h"

#include "Kismet/GameplayStatics.h"
#include "Projectiles/HomingProjectile.h"

AHomingProjectile* UProjectileManagerSubsystem::SpawnHomingProjectile(const FTransform& ProjectileTransform, const float ProjectileSpeed, const TSubclassOf<AHomingProjectile>& ProjectileClass, AActor* TargetActor) const
{
	if (!ProjectileClass)
	{
		UE_LOG(LogTemp, Error, TEXT("UProjectileManagerSubsystem::SpawnHomingProjectile - ProjectileClass is null"));
		return nullptr;
	}
	
	AHomingProjectile* Projectile = GetWorld()->SpawnActorDeferred<AHomingProjectile>(ProjectileClass, ProjectileTransform);

	const TWeakObjectPtr<AActor> ActorPointer = TargetActor;
	if (!ActorPointer.IsValid())
	{
		UE_LOG(LogTemp, Error, TEXT("UProjectileManagerSubsystem::SpawnHomingProjectile - TargetActor is invalid"));
		return nullptr;
	}
	
	Projectile->InitHomingProjectile(ProjectileSpeed, ActorPointer);
	UGameplayStatics::FinishSpawningActor(Projectile, ProjectileTransform);

	return Projectile;
}
