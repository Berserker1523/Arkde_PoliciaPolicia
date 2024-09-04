#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PP_CharacterActionState.h"
#include "PP_IdleState.generated.h"

class APP_Character;
class UPP_CharacterActionsStateModel;

UCLASS(ClassGroup = (Policia), meta = (BlueprintSpawnableComponent))
class POLICIAPOLICIA_API UPP_IdleState : public UActorComponent, public IPP_CharacterActionState
{
	GENERATED_BODY()

protected:
	APP_Character* Character;

	UPP_CharacterActionsStateModel* StateModel;

public:
	UPP_IdleState();

	virtual void BeginPlay() override;

	virtual void EnterState() override;
	virtual void ExitState() override;
	virtual void HandleInput(FName InputName, bool bPressed) override;
};
