#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PP_Projectile.generated.h"

class USphereComponent;
class UStaticMeshComponent;
class UProjectileMovementComponent;
class UParticleSystem;
struct FTimerHandle;

UCLASS()
class POLICIAPOLICIA_API APP_Projectile : public AActor
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USphereComponent* ProjectileCollisionComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* ProjectileMeshComponent;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UProjectileMovementComponent* ProjectileMovementComponent;

private:
	FTimerHandle ExplosionTimerHandle;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Hit")
	TSubclassOf<UDamageType> HitDamageType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hit")
	float HitDamage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Explosion")
	float ExplosionDelaySeconds;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
	TSubclassOf<UDamageType> ExplosionDamageType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Explosion")
	float ExplosionDamage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Explosion")
	float ExplosionRadius;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Explosion")
	UParticleSystem* ExplosionEffect;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Explosion|Debug")
	bool bDrawDebugSphere;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Explosion|Debug")
	float DebugSphereDuration;

public:	
	APP_Projectile();

protected:
	virtual void BeginPlay() override;

private:
	UFUNCTION()
	void CheckHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	void MakeHitDamage(AActor* OtherActor, const FHitResult& Hit);

	void Explode();
};
