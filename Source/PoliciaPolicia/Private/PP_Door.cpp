#include "PP_Door.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "PP_Character.h"

APP_Door::APP_Door()
{
	PrimaryActorTick.bCanEverTick = false;
	OpenAngle = -90.0f;
	DoorTag = "KeyA";

	CustomRootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("CustomRoot"));
	RootComponent = CustomRootComponent;

	DoorFrameComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorFrame"));
	DoorFrameComponent->SetupAttachment(CustomRootComponent);

	DoorComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Door"));
	DoorComponent->SetupAttachment(CustomRootComponent);

	KeyZoneColliderComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("KeyZoneCollider"));

	KeyZoneColliderComponent->SetupAttachment(CustomRootComponent);
	KeyZoneColliderComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	KeyZoneColliderComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
	KeyZoneColliderComponent->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
}

void APP_Door::BeginPlay()
{
	Super::BeginPlay();
	KeyZoneColliderComponent->OnComponentBeginOverlap.AddDynamic(this, &APP_Door::CheckKeyFromPlayer);
}

void APP_Door::CheckKeyFromPlayer(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (bIsOpen)
		return;

	if (!IsValid(OtherActor))
		return;

	APP_Character* OverlappedCharacter = Cast<APP_Character>(OtherActor);
	if (IsValid(OverlappedCharacter) && OverlappedCharacter->HasKey(DoorTag))
		OpenDoor();
}

void APP_Door::OpenDoor()
{
	//FRotator rotator = FRotator(0.0f, OpenAngle, 0.0f);
	//DoorComponent->SetRelativeRotation(rotator);
	bIsOpen = true;
	BP_OpenDoor();
}
