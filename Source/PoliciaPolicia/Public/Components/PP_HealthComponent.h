// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PP_HealthComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class POLICIAPOLICIA_API UPP_HealthComponent : public UActorComponent
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadWrite, Category = "Health Component")
	float Health;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health Component", meta = (ClampMin = 0.0, UIMin = 0.0))
	float MaxHealth;

	UPROPERTY(BlueprintReadOnly, Category = "Health Component")
	AActor* MyOwner;

public:	
	// Sets default values for this component's properties
	UPP_HealthComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UFUNCTION()
	void TakingDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);
};
