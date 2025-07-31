// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HomingProjectile.generated.h"

class UNiagaraSystem;
class UCapsuleComponent;

UCLASS()
class HOMINGMISSILESPLUGIN_API AHomingProjectile : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AHomingProjectile();

	void TriggerDestruction();
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void InitHomingProjectile(const float InProjectileSpeed, const TWeakObjectPtr<AActor> InTargetActor, USoundWave* OnHitSound);


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	TObjectPtr<UCapsuleComponent> CollisionComponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	TObjectPtr<UStaticMeshComponent> ProjectileMesh;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Homing Missile")
	TWeakObjectPtr<AActor> TargetActor;
	UPROPERTY(EditAnywhere, Category = "Homing Missile")
	float Speed;
	UPROPERTY(EditAnywhere, Category = "Homing Missile")
	float Damage;
	UPROPERTY(EditAnywhere, Category = "Homing Missile")
	float DamageRadius;

	bool bIsGliding = false;
	UPROPERTY()
	USoundWave* OnHitSound;

	UFUNCTION()
	void OnHitTarget(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit );
	UPROPERTY(EditAnywhere, Category = "Homing Missile")
	TObjectPtr<UNiagaraSystem> OnHitParticleSystem;
};
