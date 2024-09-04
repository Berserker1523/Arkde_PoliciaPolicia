#include "PP_DoorKey.h"
#include "Components/StaticMeshComponent.h"
#include "PP_Character.h"

APP_DoorKey::APP_DoorKey()
{
	KeyMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("KeyMeshComponent"));
	KeyMeshComponent->SetupAttachment(RootComponent);
	KeyMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	KeyTag = "KeyA";
}

void APP_DoorKey::Pickup(APP_Character* PickupCharacter)
{
	Super::Pickup(PickupCharacter);
	PickupCharacter->AddKey(KeyTag);
	Destroy();
}
