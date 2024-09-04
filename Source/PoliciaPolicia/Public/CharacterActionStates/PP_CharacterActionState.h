#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "PP_CharacterActionState.generated.h"

UINTERFACE(MinimalAPI)
class UPP_CharacterActionState : public UInterface
{
	GENERATED_BODY()
};

class POLICIAPOLICIA_API IPP_CharacterActionState
{
	GENERATED_BODY()

public:
	virtual void EnterState() = 0;
	virtual void ExitState() = 0;
	virtual void HandleInput(FName InputName, bool bPressed) = 0;
};
