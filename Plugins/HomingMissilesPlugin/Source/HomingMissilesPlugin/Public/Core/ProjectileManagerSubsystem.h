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

	UFUNCTION(BlueprintCallable, Category="HomingMissilesPlugin")
	AHomingProjectile* SpawnHomingProjectile(
		const FTransform& ProjectileTransform,
		const float ProjectileSpeed,
		const TSubclassOf<AHomingProjectile>& ProjectileClass,
		AActor* TargetActor,
		USoundWave* LaunchSound,
		USoundWave* OnHitSound) const;
};
