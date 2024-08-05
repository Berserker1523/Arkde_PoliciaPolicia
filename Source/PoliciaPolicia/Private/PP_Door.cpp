#include "PP_Door.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "PP_Character.h"

// Sets default values
APP_Door::APP_Door()
{
	// Set this actor to call Tick() every frame. You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
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

// Called when the game starts or when spawned
void APP_Door::BeginPlay()
{
	Super::BeginPlay();
	KeyZoneColliderComponent->OnComponentBeginOverlap.AddDynamic(this, &APP_Door::CheckKeyFromPlayer);
}

void APP_Door::CheckKeyFromPlayer(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (bIsOpen)
		return;

	if (IsValid(OtherActor))
	{
		APP_Character* OverlappedCharacter = Cast<APP_Character>(OtherActor);
		if (IsValid(OverlappedCharacter) && OverlappedCharacter->HasKey(DoorTag))
			OpenDoor();
	}
}

// Called every frame
void APP_Door::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APP_Door::OpenDoor()
{
	//FRotator rotator = FRotator(0.0f, OpenAngle, 0.0f);
	//DoorComponent->SetRelativeRotation(rotator);
	bIsOpen = true;
	BP_OpenDoor();
}
