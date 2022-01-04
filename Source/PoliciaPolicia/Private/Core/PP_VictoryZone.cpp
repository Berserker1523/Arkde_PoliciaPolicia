// Fill out your copyright notice in the Description page of Project Settings.


#include "PP_VictoryZone.h"
#include "Components/BoxComponent.h"
#include "PP_Character.h"
#include "PP_GameMode.h"

// Sets default values
APP_VictoryZone::APP_VictoryZone()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	VictoryZoneComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("VictoryZoneComponent"));
	RootComponent = VictoryZoneComponent;

	VictoryZoneComponent->SetBoxExtent(FVector(100.0f));
}

// Called when the game starts or when spawned
void APP_VictoryZone::BeginPlay()
{
	Super::BeginPlay();

	GameModeReference = Cast<APP_GameMode>(GetWorld()->GetAuthGameMode());
}

// Called every frame
void APP_VictoryZone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APP_VictoryZone::NotifyActorBeginOverlap(AActor* OtherActor)
{
	if (IsValid(OtherActor) && IsValid(GameModeReference))
	{
		APP_Character* PPCharacter = Cast<APP_Character>(OtherActor);
		if (IsValid(PPCharacter)) 
		{
			GameModeReference->Victory(PPCharacter);
		}
	}
}

