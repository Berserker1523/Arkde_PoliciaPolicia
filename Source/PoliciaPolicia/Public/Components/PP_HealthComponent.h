#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PP_HealthComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_SixParams(FOnHealthChangeSignature, UPP_HealthComponent*, HealthComponent, AActor*, DamagedActor, float, Damage, const UDamageType*, DamageType, AController*, InstigatedBy, AActor*, DamageCauser);

UCLASS(ClassGroup = (Policia), meta = (BlueprintSpawnableComponent))
class POLICIAPOLICIA_API UPP_HealthComponent : public UActorComponent
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Debug")
	bool bDebug;

	UPROPERTY(BlueprintReadOnly, Category = "Health Component")
	bool bIsDead;

	UPROPERTY(BlueprintReadWrite, Category = "Health Component")
	float Health;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health Component", meta = (ClampMin = 0.0, UIMin = 0.0))
	float MaxHealth;

	UPROPERTY(BlueprintReadOnly, Category = "Health Component")
	AActor* MyOwner;

public:
	UPROPERTY(BlueprintAssignable)
	FOnHealthChangeSignature OnHealthChangeDelegate;

public:
	UPP_HealthComponent();

	UFUNCTION(BlueprintCallable)
	bool IsDead() const { return bIsDead; };

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void TakingDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);
};
