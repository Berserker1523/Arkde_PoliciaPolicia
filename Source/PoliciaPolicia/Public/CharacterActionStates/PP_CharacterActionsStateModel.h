#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PP_CharacterActionsStateModel.generated.h"

class IPP_CharacterActionState;
class APP_Character;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class POLICIAPOLICIA_API UPP_CharacterActionsStateModel : public UActorComponent
{
	GENERATED_BODY()

public:
	static const FName WeaponAction;
	static const FName MeleeAction;

	IPP_CharacterActionState* IdleState;
	IPP_CharacterActionState* MeleeState;
	IPP_CharacterActionState* WeaponState;

private:
	IPP_CharacterActionState* CurrentState;

public:
	UPP_CharacterActionsStateModel();

	virtual void BeginPlay() override;

	void SetState(IPP_CharacterActionState* NewState);
	void StopMelee();

private:
	void InitializeStates(APP_Character* Character);
	void SetupInputs(APP_Character* Character);

	void StartWeaponAction();
	void StopWeaponAction();
	void StartMelee();
};
