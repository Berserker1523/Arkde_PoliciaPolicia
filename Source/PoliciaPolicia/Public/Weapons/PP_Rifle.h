#pragma once

#include "CoreMinimal.h"
#include "Weapons/PP_Weapon.h"
#include "PP_Rifle.generated.h"

class UParticleSystem;
struct FCollisionQueryParams;
struct FTimerHandle;

/**
 *
 */
UCLASS()
class POLICIAPOLICIA_API APP_Rifle : public APP_Weapon
{
	GENERATED_BODY()

public:

	APP_Rifle();

protected:
	FCollisionQueryParams TraceCollisionQueryParams;

	FTimerHandle FireRateTimerHandle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	float FireRate;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "LineTrace|Debug")
	bool bDrawLineTrace;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "LineTrace")
	float TraceLenght;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Effects")
	FName MuzzleSocketName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Effects")
	FName TraceParamName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Effects")
	UParticleSystem* MuzzleEffect;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Effects")
	UParticleSystem* HumanImpactEffect;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Effects")
	UParticleSystem* ImpactEffect;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Effects")
	UParticleSystem* TraceEffect;

protected:

	virtual void StartAction() override;

	virtual void StopAction() override;

	virtual void SetCharacterOwner(ACharacter* NewOwner) override;

private:
	void Fire();

	void ManageHit(FVector EyeLocation, FVector& TraceEndPoint, FVector ShotDirection);

	void CreateTraceParticle(FVector TraceEndPoint);
};
