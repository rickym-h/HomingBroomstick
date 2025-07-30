// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FlyingBat.generated.h"

class USphereComponent;

UCLASS()
class HOMINGBROOMSTICK_API AFlyingBat : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AFlyingBat();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UStaticMeshComponent> BatMesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<USphereComponent> CollisionSphere;

	FVector TargetLocation;
	float Speed = 1000.f;
	FVector GetRandomLocationInRadius(const float Radius) const;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
