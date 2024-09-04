#include "PP_CharacterActionsStateModel.h"
#include "PP_Character.h"
#include "PP_CharacterActionState.h"
#include "PP_IdleState.h"
#include "PP_MeleeState.h"
#include "PP_WeaponState.h"
#include "Components/InputComponent.h"

const FName UPP_CharacterActionsStateModel::WeaponAction(TEXT("WeaponAction"));
const FName UPP_CharacterActionsStateModel::MeleeAction(TEXT("Melee"));

UPP_CharacterActionsStateModel::UPP_CharacterActionsStateModel()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UPP_CharacterActionsStateModel::BeginPlay()
{
	Super::BeginPlay();
	APP_Character* Character = Cast<APP_Character>(GetOwner());
	InitializeStates(Character);
	SetupInputs(Character);
}

void UPP_CharacterActionsStateModel::InitializeStates(APP_Character* Character)
{
	IdleState = Cast<IPP_CharacterActionState>(Character->GetIdleStateComponent());
	MeleeState = Cast<IPP_CharacterActionState>(Character->GetMeleeStateComponent());
	WeaponState = Cast<IPP_CharacterActionState>(Character->GetWeaponStateComponent());
	SetState(IdleState);
}

void UPP_CharacterActionsStateModel::SetupInputs(APP_Character* Character)
{
	UInputComponent* InputComponent = Character->FindComponentByClass<UInputComponent>();

	InputComponent->BindAction(WeaponAction, IE_Pressed, this, &UPP_CharacterActionsStateModel::StartWeaponAction);
	InputComponent->BindAction(WeaponAction, IE_Released, this, &UPP_CharacterActionsStateModel::StopWeaponAction);
	InputComponent->BindAction(MeleeAction, IE_Pressed, this, &UPP_CharacterActionsStateModel::StartMelee);
}

void UPP_CharacterActionsStateModel::SetState(IPP_CharacterActionState* NewState)
{
	if (CurrentState)
		CurrentState->ExitState();

	CurrentState = NewState;

	if (CurrentState)
		CurrentState->EnterState();
}

void UPP_CharacterActionsStateModel::StartWeaponAction()
{
	CurrentState->HandleInput(WeaponAction, true);
}

void UPP_CharacterActionsStateModel::StopWeaponAction()
{
	CurrentState->HandleInput(WeaponAction, false);
}

void UPP_CharacterActionsStateModel::StartMelee()
{
	CurrentState->HandleInput(MeleeAction, true);
}

void UPP_CharacterActionsStateModel::StopMelee()
{
	CurrentState->HandleInput(MeleeAction, false);
}
