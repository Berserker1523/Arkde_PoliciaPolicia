#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PP_CharacterActionState.h"
#include "PP_MeleeState.generated.h"

class APP_Character;
class UPP_CharacterActionsStateModel;
class UAnimInstance;
class UAnimMontage;

UCLASS(ClassGroup = (Policia), meta = (BlueprintSpawnableComponent))
class POLICIAPOLICIA_API UPP_MeleeState : public UActorComponent, public IPP_CharacterActionState
{
	GENERATED_BODY()

protected:
	APP_Character* Character;

	UPP_CharacterActionsStateModel* StateModel;

	UAnimInstance* MyAnimInstance;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Melee")
	bool bCanMakeCombos;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Melee")
	float MaxComboMultiplier;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Melee")
	float MeleeDamage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Animation")
	UAnimMontage* MeleeMontage;

	UPROPERTY(BlueprintReadOnly, Category = "Melee")
	bool bIsComboEnabled;

	UPROPERTY(BlueprintReadOnly, Category = "Melee", meta = (EditCondition = bCanMakeCombos, ClampMin = 1.0, UIMin = 1.0))
	float CurrentComboMultiplier;

public:
	UPP_MeleeState();

	virtual void BeginPlay() override;

	virtual void EnterState() override;
	virtual void ExitState() override;
	virtual void HandleInput(FName InputName, bool bPressed) override;

	UFUNCTION(BlueprintCallable)
	void SetComboEnabled(bool NewState);

	UFUNCTION(BlueprintCallable)
	void ResetCombo();

	UFUNCTION()
	void MakeMeleeDamage(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

private:
	void PlayAnimation();
	void Combo();
};
