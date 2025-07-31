// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectiles/HomingProjectile.h"

#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"


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

void AHomingProjectile::TriggerDestruction()
{
	if (OnHitParticleSystem)
	{
		UNiagaraComponent* NiagaraComp = UNiagaraFunctionLibrary::SpawnSystemAtLocation(
			GetWorld(),
			OnHitParticleSystem,
			GetActorLocation(),
			FRotator::ZeroRotator,
			FVector(1),
			true,
			true,
			ENCPoolMethod::None,
			false
			);
	}
	
	UGameplayStatics::ApplyRadialDamage(
		GetWorld(),
		1,
		GetActorLocation(),
		600.f,
		UDamageType::StaticClass(),
		TArray<AActor*>(),
		this,
		UGameplayStatics::GetPlayerController(GetWorld(), 0),
		true
		);

	if (OnHitSound)
	{
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), OnHitSound, GetActorLocation());
	}

	Destroy();
}

// Called when the game starts or when spawned
void AHomingProjectile::BeginPlay()
{
	Super::BeginPlay();

	OnActorHit.AddUniqueDynamic(this, &AHomingProjectile::OnHitTarget);
}

void AHomingProjectile::OnHitTarget(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit)
{
	UE_LOG(LogTemp, Warning, TEXT("Hit Target: %p"), *OtherActor->GetActorNameOrLabel());
	
	TriggerDestruction();
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

	} else if (!bIsGliding)
	{
		// Target is invalid, possibly another broomstick has destroyed it - begin gliding until destruction
		bIsGliding = true;

		FTimerHandle DestructionTimerHandle;
		
		GetWorld()->GetTimerManager().SetTimer(
			DestructionTimerHandle,
			this,
			&AHomingProjectile::TriggerDestruction,
			2.f,
			false);
	}
	
	// Move towards the target
	// Since we are already facing the target, only have to add a local offset instead of a world offset
	AddActorLocalOffset(
		FVector(0, 0, Speed * DeltaTime),
		true
		);
	
}

void AHomingProjectile::InitHomingProjectile(const float InProjectileSpeed, const TWeakObjectPtr<AActor> InTargetActor, USoundWave* InOnHitSound)
{
	Speed = InProjectileSpeed;
	TargetActor = InTargetActor;
	OnHitSound = InOnHitSound;
}
