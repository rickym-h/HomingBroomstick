// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "ProjectileManagerSubsystem.generated.h"

class AHomingProjectile;
/**
 * Subsystem with functions to spawn projectiles from anywhere in the game - without needing to create a class instance.
 */
UCLASS()
class HOMINGMISSILESPLUGIN_API UProjectileManagerSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()

public:

	/**
	 * Spawns a homing projectile which should follow its target until it hits, and then explodes.
	 * @param ProjectileTransform The initial projectile location, rotation, and scale.
	 * @param ProjectileSpeed The projectile movement speed.
	 * @param ProjectileClass The projectile class. Replace it with overriden blueprint classes for different visuals.
	 * @param TargetActor The actor which this projectile should move towards
	 * @param LaunchSound The sound effect that should play when the projectile is spawned 
	 * @param OnHitSound The sound effect that should play when the projectile hit its target
	 * @return The projectile actor itself after being spawned.
	 */
	UFUNCTION(BlueprintCallable, Category="HomingMissilesPlugin")
	AHomingProjectile* SpawnHomingProjectile(
		const FTransform& ProjectileTransform,
		const float ProjectileSpeed,
		const TSubclassOf<AHomingProjectile>& ProjectileClass,
		AActor* TargetActor,
		USoundWave* LaunchSound,
		USoundWave* OnHitSound) const;
};
