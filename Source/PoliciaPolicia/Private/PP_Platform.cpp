// Fill out your copyright notice in the Description page of Project Settings.


#include "PP_Platform.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
APP_Platform::APP_Platform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CustomRootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("CustomRoot"));
	RootComponent = CustomRootComponent;

	PlatformMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PlatformMesh"));
	PlatformMeshComponent->SetupAttachment(CustomRootComponent);

	bIsGoingUp = true;
	Speed = 10.0f;
	MinHeight = 0.0f;
	MaxHeight = 50.0f;
}

// Called when the game starts or when spawned
void APP_Platform::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APP_Platform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Move();

}

void APP_Platform::Move()
{
	FVector upDirection = UKismetMathLibrary::GetUpVector(GetActorRotation());
	if (!bIsGoingUp) {
		upDirection *= -1;
	}

	FVector currentVelocity = upDirection * Speed;
	FVector newPosition = GetActorLocation() + currentVelocity;
	SetActorLocation(newPosition);

	FVector currentLocation = GetActorLocation();
	if (currentLocation.Z >= MaxHeight || currentLocation.Z <= MinHeight) {
		bIsGoingUp = !bIsGoingUp;
	}
}
