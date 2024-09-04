#include "Weapons/PP_Rifle.h"
#include "PoliciaPolicia.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystem.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "DrawDebugHelpers.h"
#include "Engine/EngineTypes.h"

APP_Rifle::APP_Rifle()
{
	TraceLenght = 10000.0f;
	MuzzleSocketName = "SCK_Muzzle";
	FireRate = 0.2F;

	TraceCollisionQueryParams.AddIgnoredActor(this);
	TraceCollisionQueryParams.bTraceComplex = true;
}

void APP_Rifle::SetCharacterOwner(ACharacter* NewOwner)
{
	Super::SetCharacterOwner(NewOwner);
	TraceCollisionQueryParams.AddIgnoredActor(NewOwner);
}

void APP_Rifle::StartAction()
{
	Super::StartAction();
	if (!GetWorld()->GetTimerManager().IsTimerActive(FireRateTimerHandle))
	{
		Fire();
		GetWorld()->GetTimerManager().SetTimer(FireRateTimerHandle, this, &APP_Rifle::Fire, FireRate, true);
	}
}

void APP_Rifle::StopAction()
{
	Super::StopAction();
	GetWorld()->GetTimerManager().ClearTimer(FireRateTimerHandle);
}

void APP_Rifle::Fire()
{
	if (!IsValid(CurrentOwnerCharacter))
		return;

	FVector EyeLocation;
	FRotator EyeRotation;

	CurrentOwnerCharacter->GetActorEyesViewPoint(EyeLocation, EyeRotation);

	FVector ShotDirection = EyeRotation.Vector();
	FVector TraceEnd = EyeLocation + (ShotDirection * TraceLenght);

	FVector TraceEndPoint = TraceEnd;

	ManageHit(EyeLocation, TraceEndPoint, ShotDirection);

	if (bDrawLineTrace)
		DrawDebugLine(GetWorld(), EyeLocation, TraceEndPoint, FColor::White, false, 1.0f, 0.0f, 1.0f);

	if (IsValid(MuzzleEffect))
		UGameplayStatics::SpawnEmitterAttached(MuzzleEffect, CurrentOwnerCharacter->GetMesh(), MuzzleSocketName);

	if (IsValid(TraceEffect))
		CreateTraceParticle(TraceEndPoint);
}

void APP_Rifle::ManageHit(FVector EyeLocation, FVector& TraceEndPoint, FVector ShotDirection)
{
	FHitResult HitResult;
	bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, EyeLocation, TraceEndPoint, COLLISION_WEAPON, TraceCollisionQueryParams);

	if (!bHit)
		return;

	TraceEndPoint = HitResult.ImpactPoint;

	AActor* HitActor = HitResult.GetActor();
	if (!IsValid(HitActor))
		return;

	UGameplayStatics::ApplyPointDamage(HitActor, Damage, ShotDirection, HitResult, CurrentOwnerCharacter->GetInstigatorController(), this, DamageType);

	ACharacter* HitCharacter = Cast<ACharacter>(HitActor);
	if (IsValid(HitCharacter) && IsValid(HumanImpactEffect))
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HumanImpactEffect, TraceEndPoint, HitResult.ImpactNormal.Rotation());
	else if (IsValid(ImpactEffect))
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactEffect, TraceEndPoint, HitResult.ImpactNormal.Rotation());
}

void APP_Rifle::CreateTraceParticle(FVector TraceEndPoint)
{
	USkeletalMeshComponent* CharacterMeshComponent = CurrentOwnerCharacter->GetMesh();
	if (!IsValid(CharacterMeshComponent))
		return;

	FVector MuzzleSocketLocation = CharacterMeshComponent->GetSocketLocation(MuzzleSocketName);
	UParticleSystemComponent* TraceComponent = UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), TraceEffect, MuzzleSocketLocation);

	if (IsValid(TraceComponent))
		TraceComponent->SetVectorParameter(TraceParamName, TraceEndPoint);
}
