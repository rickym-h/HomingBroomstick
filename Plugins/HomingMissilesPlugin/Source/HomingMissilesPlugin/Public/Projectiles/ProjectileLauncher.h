// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProjectileLauncher.generated.h"

class AHomingProjectile;
/**
* AProjectileLauncher is an actor, which can be interacted with to launch projectiles. This should be inherited from to create launchers like cannons, ballistas, etc
*/
UCLASS()
class HOMINGMISSILESPLUGIN_API AProjectileLauncher : public AActor
{
	GENERATED_BODY()

public:
	AProjectileLauncher();

	/**
	 * Fires a projectile at the target.
	 * @param Target The actor which the projectile should "home" towards
	 */
	UFUNCTION(BlueprintCallable, Category="Projectile")
	void LaunchProjectile(AActor* Target);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UStaticMeshComponent> BaseMesh;
	
	/**
	 * A scene component in the location where the projectile is spawned
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<USceneComponent> ProjectileLaunchPoint;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AHomingProjectile> ProjectileClass;
	/**
	 * Sound effect which plays when the projectile is spawned/launched.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USoundWave* LaunchSoundEffect;
	/**
	 * Sound effect which plays when the projectile hit its target
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USoundWave* OnHitSoundEffect;
};
