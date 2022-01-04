// Fill out your copyright notice in the Description page of Project Settings.


#include "PP_ANEnableAction.h"
#include "PP_Character.h"
#include "Components/SkeletalMeshComponent.h"

void UPP_ANEnableAction::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	AActor* CharacterActor = MeshComp->GetOwner();
	if (IsValid(CharacterActor))
	{
		APP_Character* Character = Cast<APP_Character>(CharacterActor);
		if (IsValid(Character))
		{
			Character->SetMeleeState(false);
		}
	}
}
