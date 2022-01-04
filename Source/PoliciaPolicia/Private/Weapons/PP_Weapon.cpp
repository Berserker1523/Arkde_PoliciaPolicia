// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/PP_Weapon.h"
#include "GameFramework/Character.h"

// Sets default values
APP_Weapon::APP_Weapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Damage = 20.0f;

}

// Called when the game starts or when spawned
void APP_Weapon::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APP_Weapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APP_Weapon::StartAction()
{
	BP_StartAction();
}

void APP_Weapon::StopAction()
{
	BP_StopAction();
}

void APP_Weapon::SetCharacterOwner(ACharacter* NewOwner)
{
	if (IsValid(NewOwner))
	{
		SetOwner(NewOwner);
		CurrentOwnerCharacter = NewOwner;
	}
}

