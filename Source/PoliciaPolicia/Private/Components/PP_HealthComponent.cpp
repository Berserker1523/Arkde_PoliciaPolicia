#include "PP_HealthComponent.h"

UPP_HealthComponent::UPP_HealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

	MaxHealth = 100.0f;
}

void UPP_HealthComponent::BeginPlay()
{
	Super::BeginPlay();

	Health = MaxHealth;

	MyOwner = GetOwner();
	if (!IsValid(MyOwner))
		return;
	MyOwner->OnTakeAnyDamage.AddDynamic(this, &UPP_HealthComponent::TakingDamage);
}

void UPP_HealthComponent::TakingDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	if (Damage <= 0.0f || bIsDead)
		return;

	Health = FMath::Clamp(Health - Damage, 0.0f, MaxHealth);

	if (Health == 0.0f)
		bIsDead = true;

	OnHealthChangeDelegate.Broadcast(this, DamagedActor, Damage, DamageType, InstigatedBy, DamageCauser);

	if(bDebug)
		UE_LOG(LogTemp, Log, TEXT("My Health is: %s"), *FString::SanitizeFloat(Health));
}
