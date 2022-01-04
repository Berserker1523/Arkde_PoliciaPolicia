// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/PP_Projectile.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Gameframework/ProjectileMovementComponent.h"

// Sets default values
APP_Projectile::APP_Projectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ProjectileCollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("ProjectileCollisionComponent"));
	RootComponent = ProjectileCollisionComponent;

	ProjectileMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileMeshComponent"));
	ProjectileMeshComponent->SetupAttachment(ProjectileCollisionComponent);

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
	ProjectileMovementComponent->InitialSpeed = 1000.0f;
	ProjectileMovementComponent->MaxSpeed = 1000.0f;
}

// Called when the game starts or when spawned
void APP_Projectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APP_Projectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

