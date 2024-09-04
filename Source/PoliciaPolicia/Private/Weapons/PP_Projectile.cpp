#include "Weapons/PP_Projectile.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Gameframework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/EngineTypes.h"
#include "DrawDebugHelpers.h"
#include "Particles/ParticleSystemComponent.h"

APP_Projectile::APP_Projectile()
{
	PrimaryActorTick.bCanEverTick = true;

	ProjectileCollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("ProjectileCollisionComponent"));
	RootComponent = ProjectileCollisionComponent;

	ProjectileMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileMeshComponent"));
	ProjectileMeshComponent->SetupAttachment(ProjectileCollisionComponent);

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
	ProjectileMovementComponent->InitialSpeed = 1000.0f;
	ProjectileMovementComponent->MaxSpeed = 1000.0f;
	ProjectileMovementComponent->bShouldBounce = true;

	HitDamage = 10.0F;
	ExplosionDelaySeconds = 3.0F;
	ExplosionDamage = 100.0F;
	ExplosionRadius = 500.0F;
	DebugSphereDuration = 1.0F;
}

void APP_Projectile::BeginPlay()
{
	Super::BeginPlay();
	ProjectileCollisionComponent->OnComponentHit.AddDynamic(this, &APP_Projectile::CheckHit);
	GetWorld()->GetTimerManager().SetTimer(ExplosionTimerHandle, this, &APP_Projectile::Explode, ExplosionDelaySeconds, false);
}
 
void APP_Projectile::CheckHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (!IsValid(OtherActor))
		return;
	MakeHitDamage(OtherActor, Hit);
}

void APP_Projectile::MakeHitDamage(AActor* OtherActor, const FHitResult& Hit)
{
	UGameplayStatics::ApplyPointDamage(OtherActor, HitDamage, Hit.Normal, Hit, GetInstigatorController(), this, HitDamageType);
}

void APP_Projectile::Explode()
{
	UGameplayStatics::ApplyRadialDamage(this, ExplosionDamage, GetActorLocation(), ExplosionRadius, ExplosionDamageType, TArray<AActor*>(), this, GetInstigatorController(), true);
	
	if(IsValid(ExplosionEffect))
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ExplosionEffect, GetActorLocation(), GetActorRotation(), FVector::OneVector * ExplosionRadius / 100.0F);

	if (bDrawDebugSphere)
		DrawDebugSphere(GetWorld(), GetActorLocation(), ExplosionRadius, 32, FColor::Red, false, DebugSphereDuration);

	Destroy();
}
