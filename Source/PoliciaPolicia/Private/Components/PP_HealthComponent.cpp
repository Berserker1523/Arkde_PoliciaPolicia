// Fill out your copyright notice in the Description page of Project Settings.


#include "PP_HealthComponent.h"

// Sets default values for this component's properties
UPP_HealthComponent::UPP_HealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	MaxHealth = 100.0f;
}


// Called when the game starts
void UPP_HealthComponent::BeginPlay()
{
	Super::BeginPlay();

	Health = MaxHealth;

	MyOwner = GetOwner();
	if (IsValid(MyOwner))
	{
		MyOwner->OnTakeAnyDamage.AddDynamic(this, &UPP_HealthComponent::TakingDamage);
	}
	
}

void UPP_HealthComponent::TakingDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	if (Damage <= 0.0f)
	{
		return;
	}

	Health = FMath::Clamp(Health - Damage, 0.0f, MaxHealth);
}

