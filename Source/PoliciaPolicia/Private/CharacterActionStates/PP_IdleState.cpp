#include "PP_IdleState.h"
#include "PP_CharacterActionsStateModel.h"
#include "PP_Character.h"

UPP_IdleState::UPP_IdleState()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UPP_IdleState::BeginPlay()
{
	Super::BeginPlay();
	Character = Cast<APP_Character>(GetOwner());
	StateModel = Character->FindComponentByClass<UPP_CharacterActionsStateModel>();
}

void UPP_IdleState::EnterState() { }

void UPP_IdleState::ExitState() { }

void UPP_IdleState::HandleInput(FName InputName, bool bPressed)
{
	if (!bPressed)
		return;

	if (InputName == UPP_CharacterActionsStateModel::WeaponAction)
		StateModel->SetState(StateModel->WeaponState);
	else if (InputName == UPP_CharacterActionsStateModel::MeleeAction)
		StateModel->SetState(StateModel->MeleeState);
}
