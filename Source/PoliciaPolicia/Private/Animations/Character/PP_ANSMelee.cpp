#include "PP_ANSMelee.h"
#include "Components/PP_MeleeCollider.h"
#include "Components/SkeletalMeshComponent.h"

void UPP_ANSMelee::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	AActor* CharacterActor = MeshComp->GetOwner();
	if (!IsValid(CharacterActor))
		return;

	UPP_MeleeCollider* MeleeCollider = CharacterActor->FindComponentByClass<UPP_MeleeCollider>();
	if (IsValid(MeleeCollider))
		MeleeCollider->SetMeleeDetectorCollision(ECollisionEnabled::QueryOnly);
}

void UPP_ANSMelee::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	AActor* CharacterActor = MeshComp->GetOwner();
	if (!IsValid(CharacterActor))
		return;

	UPP_MeleeCollider* MeleeCollider = CharacterActor->FindComponentByClass<UPP_MeleeCollider>();
	if (IsValid(MeleeCollider))
		MeleeCollider->SetMeleeDetectorCollision(ECollisionEnabled::NoCollision);
}
