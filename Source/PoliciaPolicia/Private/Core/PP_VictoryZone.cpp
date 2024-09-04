#include "PP_VictoryZone.h"
#include "Components/BoxComponent.h"
#include "PP_Character.h"
#include "PP_GameMode.h"

APP_VictoryZone::APP_VictoryZone()
{
	PrimaryActorTick.bCanEverTick = false;

	VictoryZoneComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("VictoryZoneComponent"));
	RootComponent = VictoryZoneComponent;

	VictoryZoneComponent->SetBoxExtent(FVector(100.0f));
}

void APP_VictoryZone::BeginPlay()
{
	Super::BeginPlay();
	GameModeReference = Cast<APP_GameMode>(GetWorld()->GetAuthGameMode());
}

void APP_VictoryZone::NotifyActorBeginOverlap(AActor* OtherActor)
{
	if (IsValid(OtherActor) && IsValid(GameModeReference))
	{
		APP_Character* PPCharacter = Cast<APP_Character>(OtherActor);
		if (IsValid(PPCharacter))
			GameModeReference->Victory(PPCharacter);
	}
}
