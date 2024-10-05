#pragma once

#include "CoreMinimal.h"
#include "Components/CapsuleComponent.h"
#include "PP_MeleeCollider.generated.h"

UCLASS()
class POLICIAPOLICIA_API UPP_MeleeCollider : public UCapsuleComponent
{
	GENERATED_BODY()
	
public:
	UPP_MeleeCollider();

	virtual void BeginPlay() override;

	void SetMeleeDetectorCollision(ECollisionEnabled::Type NewCollisionState);
};
