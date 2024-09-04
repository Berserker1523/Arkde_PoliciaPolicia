#pragma once

#include "CoreMinimal.h"
#include "Components/CapsuleComponent.h"
#include "PP_MeleeCollider.generated.h"

class UPP_MeleeState;

UCLASS()
class POLICIAPOLICIA_API UPP_MeleeCollider : public UCapsuleComponent
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(BlueprintreadOnly, Category = "Components")
	UPP_MeleeState* MeleeState;

public:
	UPP_MeleeCollider();

	virtual void BeginPlay() override;

	void SetMeleeDetectorCollision(ECollisionEnabled::Type NewCollisionState);
};
