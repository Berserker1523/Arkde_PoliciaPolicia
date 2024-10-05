#include "PP_MeleeCollider.h"
#include "CharacterActionStates/PP_MeleeState.h"
#include "PoliciaPolicia.h"

UPP_MeleeCollider::UPP_MeleeCollider()
{
	PrimaryComponentTick.bCanEverTick = false;

	SetCollisionResponseToAllChannels(ECR_Ignore);
	SetCollisionResponseToChannel(COLLISION_ENEMY, ECR_Overlap);
	SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void UPP_MeleeCollider::BeginPlay()
{
	Super::BeginPlay();
	UPP_MeleeState* MeleeState = GetOwner()->FindComponentByClass<UPP_MeleeState>();
	OnComponentBeginOverlap.AddDynamic(MeleeState, &UPP_MeleeState::MakeMeleeDamage);
}

void UPP_MeleeCollider::SetMeleeDetectorCollision(ECollisionEnabled::Type NewCollisionState)
{
	SetCollisionEnabled(NewCollisionState);
}
