// Fill out your copyright notice in the Description page of Project Settings.


#include "PP_ANSMelee.h"
#include "PP_Character.h"
#include "Components/SkeletalMeshComponent.h"

void UPP_ANSMelee::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	AActor* CharacterActor = MeshComp->GetOwner();
	if(IsValid(CharacterActor))
	{
		APP_Character* Character = Cast<APP_Character>(CharacterActor);
		if (IsValid(Character))
		{
			Character->SetMeleeDetectorCollision(ECollisionEnabled::QueryOnly);
		}
	}
}

void UPP_ANSMelee::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	AActor* CharacterActor = MeshComp->GetOwner();
	if (IsValid(CharacterActor))
	{
		APP_Character* Character = Cast<APP_Character>(CharacterActor);
		if (IsValid(Character))
		{
			Character->SetMeleeDetectorCollision(ECollisionEnabled::NoCollision);
		}
	}
}
