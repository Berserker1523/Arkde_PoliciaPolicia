// Fill out your copyright notice in the Description page of Project Settings.

#include "PP_Item.h"
#include "Components/SphereComponent.h"
#include "..\..\Public\Items\PP_Item.h"
#include "PP_Character.h"

// Sets default values
APP_Item::APP_Item()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MainColliderComponent = CreateDefaultSubobject<USphereComponent>(TEXT("MainColliderComponent"));
	MainColliderComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	MainColliderComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
	MainColliderComponent->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block);
	MainColliderComponent->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Block);
	MainColliderComponent->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	RootComponent = MainColliderComponent;
}

// Called when the game starts or when spawned
void APP_Item::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APP_Item::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APP_Item::NotifyActorBeginOverlap(AActor* otherActor)
{
	Super::NotifyActorBeginOverlap(otherActor);

	if (IsValid(otherActor)) 
	{
		APP_Character* OverlappedCharacter = Cast<APP_Character>(otherActor);
		if (IsValid(OverlappedCharacter)) {
			Pickup(OverlappedCharacter);
		}
	}
}

void APP_Item::Pickup(APP_Character* PickupCharacter)
{
	BP_Pickup(PickupCharacter);
}