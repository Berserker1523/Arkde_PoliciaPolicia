#include "PP_GameMode.h"
#include "PP_Character.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/PawnMovementComponent.h"

void APP_GameMode::Victory(APP_Character* Character)
{
	Character->DisableInput(nullptr);
	BP_Victory(Character);
}

void APP_GameMode::GameOver(APP_Character* Character)
{
	Character->GetMovementComponent()->StopMovementImmediately();
	Character->GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	Character->DetachFromControllerPendingDestroy();
	Character->SetLifeSpan(5.0f);

	BP_GameOver(Character);
}
