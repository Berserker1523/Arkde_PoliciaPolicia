// Fill out your copyright notice in the Description page of Project Settings.


#include "PP_Door.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
APP_Door::APP_Door()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	OpenAngle = -90.0f;
	CustomRootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("CustomRoot"));
	RootComponent = CustomRootComponent;

	DoorFrameComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorFrame"));
	DoorFrameComponent->SetupAttachment(CustomRootComponent);

	DoorComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Door"));
	DoorComponent->SetupAttachment(CustomRootComponent);
}

// Called when the game starts or when spawned
void APP_Door::BeginPlay()
{
	Super::BeginPlay();
	OpenDoor();
}

// Called every frame
void APP_Door::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APP_Door::OpenDoor() 
{
	FRotator rotator = FRotator(0.0f, OpenAngle, 0.0f);
	DoorComponent->SetRelativeRotation(rotator);
}

