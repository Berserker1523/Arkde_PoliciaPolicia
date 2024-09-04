#include "PP_Item.h"
#include "Components/SphereComponent.h"
#include "PP_Character.h"

APP_Item::APP_Item()
{
	PrimaryActorTick.bCanEverTick = false;

	MainColliderComponent = CreateDefaultSubobject<USphereComponent>(TEXT("MainColliderComponent"));
	RootComponent = MainColliderComponent;

	MainColliderComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	MainColliderComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
	MainColliderComponent->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block);
	MainColliderComponent->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Block);
	MainColliderComponent->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
}

void APP_Item::NotifyActorBeginOverlap(AActor* otherActor)
{
	Super::NotifyActorBeginOverlap(otherActor);

	if (!IsValid(otherActor))
		return;
	 
	APP_Character* OverlappedCharacter = Cast<APP_Character>(otherActor);
	if (IsValid(OverlappedCharacter))
		Pickup(OverlappedCharacter);
}

void APP_Item::Pickup(APP_Character* PickupCharacter)
{
	BP_Pickup(PickupCharacter);
}
