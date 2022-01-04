// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapons/PP_Weapon.h"
#include "PP_GrenadeLauncher.generated.h"

class APP_Projectile;

/**
 * 
 */
UCLASS()
class POLICIAPOLICIA_API APP_GrenadeLauncher : public APP_Weapon
{
	GENERATED_BODY()

public:
	APP_GrenadeLauncher();

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Grenade Launcher")
	TSubclassOf<APP_Projectile> ProjectileClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Effects")
	FName MuzzleSocketName;

protected:

	virtual void StartAction() override;

	virtual void StopAction() override;
	
};
