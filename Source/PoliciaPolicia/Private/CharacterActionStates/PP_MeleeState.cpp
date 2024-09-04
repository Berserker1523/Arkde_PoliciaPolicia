#include "PP_MeleeState.h"
#include "PP_CharacterActionsStateModel.h"
#include "PP_Character.h"
#include "Animation/AnimInstance.h"
#include "Animation/AnimMontage.h"
#include "Kismet/GameplayStatics.h"

UPP_MeleeState::UPP_MeleeState()
{
	PrimaryComponentTick.bCanEverTick = false;

	bCanMakeCombos = true;
	MeleeDamage = 50.0f;
	MaxComboMultiplier = 4.0f;
	CurrentComboMultiplier = 1.0f;
}

void UPP_MeleeState::BeginPlay()
{
	Super::BeginPlay();
	Character = Cast<APP_Character>(GetOwner());
	StateModel = Character->FindComponentByClass<UPP_CharacterActionsStateModel>();
	MyAnimInstance = Character->GetMesh()->GetAnimInstance();
}

void UPP_MeleeState::EnterState()
{
	PlayAnimation();
}

void UPP_MeleeState::ExitState() { }

void UPP_MeleeState::HandleInput(FName InputName, bool bPressed)
{
	if (InputName == UPP_CharacterActionsStateModel::MeleeAction && !bPressed)
		StateModel->SetState(StateModel->IdleState);
	else if (InputName == UPP_CharacterActionsStateModel::MeleeAction && bPressed)
		Combo();
}

void UPP_MeleeState::PlayAnimation()
{
	if (IsValid(MyAnimInstance) && IsValid(MeleeMontage))
		MyAnimInstance->Montage_Play(MeleeMontage);
}

void UPP_MeleeState::Combo()
{
	if (!bCanMakeCombos)
		return;

	if (!bIsComboEnabled || CurrentComboMultiplier >= MaxComboMultiplier)
		return;

	CurrentComboMultiplier++;
	SetComboEnabled(false);
	PlayAnimation();
}

void UPP_MeleeState::SetComboEnabled(bool NewState)
{
	bIsComboEnabled = NewState;
}

void UPP_MeleeState::ResetCombo()
{
	SetComboEnabled(false);
	CurrentComboMultiplier = 1.0f;
}

void UPP_MeleeState::MakeMeleeDamage(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (IsValid(OtherActor))
		UGameplayStatics::ApplyPointDamage(OtherActor, MeleeDamage * CurrentComboMultiplier, SweepResult.Location, SweepResult, Character->GetInstigatorController(), Character, nullptr);
}
