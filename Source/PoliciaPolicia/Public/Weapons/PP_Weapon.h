#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PP_Weapon.generated.h"

class UDamageType;
class ACharacter;

UCLASS()
class POLICIAPOLICIA_API APP_Weapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APP_Weapon();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon")
	float Damage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
	TSubclassOf<UDamageType> DamageType;

	ACharacter* CurrentOwnerCharacter;

protected:
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Weapon")
	void BP_StartAction();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Weapon")
	void BP_StopAction();

public:
	UFUNCTION(BlueprintCallable)
	virtual void StartAction();

	UFUNCTION(BlueprintCallable)
	virtual void StopAction();

	UFUNCTION(BlueprintCallable)
	virtual void SetCharacterOwner(ACharacter* NewOwner);
};
