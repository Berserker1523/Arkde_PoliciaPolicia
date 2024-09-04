#include "PP_WeaponState.h"
#include "PP_CharacterActionsStateModel.h"
#include "PP_Character.h"
#include "Weapons/PP_Weapon.h"
#include "Engine/World.h"
#include "Components/SkeletalMeshComponent.h"

UPP_WeaponState::UPP_WeaponState()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UPP_WeaponState::BeginPlay()
{
	Super::BeginPlay();
	Character = Cast<APP_Character>(GetOwner());
	StateModel = Character->FindComponentByClass<UPP_CharacterActionsStateModel>();
	CreateInitialWeapon();
}

void UPP_WeaponState::CreateInitialWeapon()
{
	if (!IsValid(InitialWeaponClass))
	{
		UE_LOG(LogTemp, Warning, TEXT("UPP_WeaponState CreateInitialWeapon: InitialWeaponClass is not valid"));
		return;
	}

	CurrentWeapon = Character->GetWorld()->SpawnActor<APP_Weapon>(InitialWeaponClass, Character->GetActorLocation(), Character->GetActorRotation());

	if (!IsValid(CurrentWeapon))
	{
		UE_LOG(LogTemp, Warning, TEXT("WeaponState CreateInitialWeapon: CurrentWeapon is not valid"));
		return;
	}

    CurrentWeapon->SetCharacterOwner(Character);
    CurrentWeapon->AttachToComponent(Character->GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, Character->GetFPSCameraSocketName());
}

void UPP_WeaponState::EnterState()
{
	if (!IsValid(CurrentWeapon))
		return;

	CurrentWeapon->StartAction();

	if (Character->GetIsRunning())
		Character->SwitchRunning();
}

void UPP_WeaponState::ExitState()
{
	if (IsValid(CurrentWeapon))
		CurrentWeapon->StopAction();
}

void UPP_WeaponState::HandleInput(FName InputName, bool bPressed)
{
	if (InputName == UPP_CharacterActionsStateModel::WeaponAction && !bPressed)
		StateModel->SetState(StateModel->IdleState);
	else if (InputName == UPP_CharacterActionsStateModel::MeleeAction && bPressed)
		StateModel->SetState(StateModel->MeleeState);
}
