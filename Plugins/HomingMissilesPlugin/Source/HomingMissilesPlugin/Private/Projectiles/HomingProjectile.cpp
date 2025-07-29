// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectiles/HomingProjectile.h"

#include "Components/CapsuleComponent.h"


// Sets default values
AHomingProjectile::AHomingProjectile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Collision Component"));
	SetRootComponent(CollisionComponent);

	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile Mesh"));
	ProjectileMesh->SetupAttachment(CollisionComponent);
	ProjectileMesh->SetCollisionProfileName(FName("NoCollision"));
	ProjectileMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	ProjectileMesh->SetCollisionResponseToAllChannels(ECR_Ignore);
}

// Called when the game starts or when spawned
void AHomingProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AHomingProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Check if the target is null or is pending garbage collection
	if (TargetActor.IsValid())
	{
		// Rotate towards the target
		const FVector Direction = (TargetActor->GetActorLocation() - GetActorLocation()).GetSafeNormal();
		const FRotator TargetRotation = Direction.Rotation() + FRotator(-90, 0, 0);
		SetActorRotation(TargetRotation);

		// Move towards the target
		// Since we are already facing the target, only have to add a local offset instead of a world offset
		AddActorLocalOffset(FVector(0, 0, Speed * DeltaTime));
	}
}

void AHomingProjectile::InitHomingProjectile(const float InProjectileSpeed, const TWeakObjectPtr<AActor> InTargetActor)
{
	Speed = InProjectileSpeed;
	TargetActor = InTargetActor;
}

