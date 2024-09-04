#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "PP_ANEnableAction.generated.h"

/**
 * 
 */
UCLASS()
class POLICIAPOLICIA_API UPP_ANEnableAction : public UAnimNotify
{
	GENERATED_BODY()
	
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
};
