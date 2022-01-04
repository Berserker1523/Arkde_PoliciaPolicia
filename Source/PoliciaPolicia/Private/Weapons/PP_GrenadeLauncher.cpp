// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/PP_GrenadeLauncher.h"
#include "Weapons/PP_Projectile.h"
#include "GameFramework/Character.h"
#include "Components/SkeletalMeshComponent.h"

APP_GrenadeLauncher::APP_GrenadeLauncher()
{
	MuzzleSocketName = "SCK_Muzzle";
}

void APP_GrenadeLauncher::StartAction()
{
	Super::StartAction();

	if (IsValid(CurrentOwnerCharacter))
	{
		USkeletalMeshComponent* CharacterMeshComponent = CurrentOwnerCharacter->GetMesh();
		if (IsValid(CharacterMeshComponent))
		{
			FVector MuzzleSocketLocation = CharacterMeshComponent->GetSocketLocation(MuzzleSocketName);
			FRotator MuzzleSocketRotattion = CharacterMeshComponent->GetSocketRotation(MuzzleSocketName);

			APP_Projectile* CurrentProjectile = GetWorld()->SpawnActor<APP_Projectile>(ProjectileClass, MuzzleSocketLocation, MuzzleSocketRotattion);
		}
	}
}

void APP_GrenadeLauncher::StopAction()
{
	Super::StopAction();
}