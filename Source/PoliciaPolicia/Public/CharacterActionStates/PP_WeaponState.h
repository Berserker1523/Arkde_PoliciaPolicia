#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PP_CharacterActionState.h"
#include "PP_WeaponState.generated.h"

class APP_Character;
class APP_Weapon;
class UPP_CharacterActionsStateModel;

UCLASS(ClassGroup = (Policia), meta = (BlueprintSpawnableComponent))
class POLICIAPOLICIA_API UPP_WeaponState : public UActorComponent, public IPP_CharacterActionState
{
	GENERATED_BODY()

protected:
	APP_Character* Character;

	UPP_CharacterActionsStateModel* StateModel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	TSubclassOf<APP_Weapon> InitialWeaponClass;

	UPROPERTY(BlueprintReadWrite, Category = "Weapon")
	APP_Weapon* CurrentWeapon;

public:
	UPP_WeaponState();

	virtual void BeginPlay() override;

	virtual void EnterState() override;
	virtual void ExitState() override;
	virtual void HandleInput(FName InputName, bool bPressed) override;

private:
	void CreateInitialWeapon();
};
