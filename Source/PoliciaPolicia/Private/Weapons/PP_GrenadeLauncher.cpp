#include "Weapons/PP_GrenadeLauncher.h"
#include "Weapons/PP_Projectile.h"
#include "GameFramework/Character.h"
#include "Components/SkeletalMeshComponent.h"
#include "Gameframework/ProjectileMovementComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

APP_GrenadeLauncher::APP_GrenadeLauncher()
{
	MuzzleSocketName = "SCK_Muzzle";
}

void APP_GrenadeLauncher::StartAction()
{
	Super::StartAction();

	if (!IsValid(CurrentOwnerCharacter))
		return;

	USkeletalMeshComponent* CharacterMeshComponent = CurrentOwnerCharacter->GetMesh();
	if (!IsValid(CharacterMeshComponent))
		return;

	FVector MuzzleSocketLocation = CharacterMeshComponent->GetSocketLocation(MuzzleSocketName);
	FRotator MuzzleSocketRotation = CharacterMeshComponent->GetSocketRotation(MuzzleSocketName);

	FVector EyeLocation;
	FRotator EyeRotation;

	CurrentOwnerCharacter->GetActorEyesViewPoint(EyeLocation, EyeRotation);

	APP_Projectile* CurrentProjectile = GetWorld()->SpawnActor<APP_Projectile>(ProjectileClass, MuzzleSocketLocation, MuzzleSocketRotation);
}
