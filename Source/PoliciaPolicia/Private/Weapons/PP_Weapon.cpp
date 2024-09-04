#include "Weapons/PP_Weapon.h"
#include "GameFramework/Character.h"

APP_Weapon::APP_Weapon()
{
	PrimaryActorTick.bCanEverTick = true;

	Damage = 20.0f;
}

void APP_Weapon::StartAction()
{
	UE_LOG(LogTemp, Log, TEXT("Weapon starts action!"));
	BP_StartAction();
}

void APP_Weapon::StopAction()
{
	UE_LOG(LogTemp, Log, TEXT("Weapon stops action!"));
	BP_StopAction();
}

void APP_Weapon::SetCharacterOwner(ACharacter* NewOwner)
{
	if (!IsValid(NewOwner))
		return;
	SetOwner(NewOwner);
	CurrentOwnerCharacter = NewOwner;
}
