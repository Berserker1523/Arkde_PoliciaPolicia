#include "PP_ANEnableAction.h"
#include "CharacterActionStates/PP_CharacterActionsStateModel.h"
#include "Components/SkeletalMeshComponent.h"

void UPP_ANEnableAction::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	AActor* CharacterActor = MeshComp->GetOwner();
	if (!IsValid(CharacterActor))
		return;

	UPP_CharacterActionsStateModel* StateModel = CharacterActor->FindComponentByClass<UPP_CharacterActionsStateModel>();
	if (IsValid(StateModel))
		StateModel->StopMelee();
}
