// Fill out your copyright notice in the Description page of Project Settings.


#include "FlyingBat.h"

#include "Components/SphereComponent.h"


// Sets default values
AFlyingBat::AFlyingBat()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionSphere = CreateDefaultSubobject<USphereComponent>("Collision Sphere");
	CollisionSphere->SetCollisionObjectType(ECC_GameTraceChannel2); // Set to be a "Bat" object type.
	CollisionSphere->SetCollisionResponseToAllChannels(ECR_Ignore);
	CollisionSphere->SetCollisionResponseToChannel(ECC_GameTraceChannel1, ECR_Block); // Block the "Projectile" object types 
	SetRootComponent(CollisionSphere);

	BatMesh = CreateDefaultSubobject<UStaticMeshComponent>("Bat Mesh");
	BatMesh->SetupAttachment(CollisionSphere);
}

// Called when the game starts or when spawned
void AFlyingBat::BeginPlay()
{
	Super::BeginPlay();

	TargetLocation = GetRandomLocationInRadius(4000.0f);
	
}

FVector AFlyingBat::GetRandomLocationInRadius(const float Radius) const
{
	const FVector CurrentLocation = GetActorLocation();
	const FVector RandomUnitVector = FMath::VRand();
	const float Distance = Radius * FMath::FRand();

	return CurrentLocation + (RandomUnitVector * Distance);
}

// Called every frame
void AFlyingBat::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (FVector::Dist(GetActorLocation(), TargetLocation) < 10.0f)
	{
		TargetLocation = GetRandomLocationInRadius(2000.0f);
	}
	UE_LOG(LogTemp, Warning, TEXT("%f"), FVector::Dist(GetActorLocation(), TargetLocation));

	// Move towards the target location - this is somewhat similar to the homing missile movement implementation
	// Rotate towards the target
	const FVector Direction = (TargetLocation - GetActorLocation()).GetSafeNormal();
	const FRotator TargetRotation = Direction.Rotation();
	SetActorRotation(TargetRotation);

	// Move towards the target
	// Since we are already facing the target, only have to add a local offset instead of a world offset
	AddActorLocalOffset(
		FVector(Speed * DeltaTime, 0, 0),
		true
		);
}

