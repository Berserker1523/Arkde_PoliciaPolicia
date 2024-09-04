#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PP_Character.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UCharacterMovementComponent;
class UPP_HealthComponent;
class UPP_IdleState;
class UPP_MeleeState;
class UPP_WeaponState;
class UPP_MeleeCollider;
class UPP_CharacterActionsStateModel;
class APP_GameMode;

UCLASS()
class POLICIAPOLICIA_API APP_Character : public ACharacter
{
	GENERATED_BODY()

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USpringArmComponent* SpringArmComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UCameraComponent* FPSCameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UCameraComponent* TPSCameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UCharacterMovementComponent* CharacterMovementComponent;

	UPROPERTY(VisibleAnywhere, BlueprintreadOnly, Category = "Components")
	UPP_HealthComponent* HealthComponent;

	UPROPERTY(VisibleAnywhere, BlueprintreadOnly, Category = "Components")
	UPP_IdleState* IdleStateComponent;

	UPROPERTY(VisibleAnywhere, BlueprintreadOnly, Category = "Components")
	UPP_MeleeState* MeleeStateComponent;

	UPROPERTY(VisibleAnywhere, BlueprintreadOnly, Category = "Components")
	UPP_WeaponState* WeaponStateComponent;

	UPROPERTY(VisibleAnywhere, BlueprintreadOnly, Category = "Components")
	UPP_MeleeCollider* MeleeColliderComponent;

	UPROPERTY(VisibleAnywhere, BlueprintreadOnly, Category = "Components")
	UPP_CharacterActionsStateModel* CharacterActionsStateModelComponent;

protected:
	UPROPERTY(BlueprintReadOnly, category = "Movement")
	float walkSpeed;

	UPROPERTY(BlueprintReadOnly, category = "Movement")
	float runSpeed;

	UPROPERTY(BlueprintReadOnly, category = "Movement")
	bool bIsRunning;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, category = "Aiming")
	bool bUseFirstPersonView;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, category = "Aiming")
	bool bIsLookInverted;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, category = "Aiming")
	FName FPSCameraSocketName;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, category = "Melee")
	FName MeleeSocketName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Key")
	TArray<FName> DoorKeys;

	APP_GameMode* GameMode;

public:
	APP_Character();

	virtual void BeginPlay() override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void AddControllerPitchInput(float value) override;

	virtual FVector GetPawnViewLocation() const override;

	void SwitchRunning();

	void AddKey(FName NewKey);
	bool HasKey(FName Key);

private:
	void MoveForward(float value);
	void MoveRight(float value);

	void SwitchView();

	UFUNCTION()
	void OnHealthChanged(UPP_HealthComponent* CurrentHealthComponent, AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser);

public:
	FName GetFPSCameraSocketName() const { return FPSCameraSocketName; }

	bool GetIsRunning() const { return bIsRunning; }

	UPP_IdleState* GetIdleStateComponent() const { return IdleStateComponent; }

	UPP_MeleeState* GetMeleeStateComponent() const { return MeleeStateComponent; }

	UPP_WeaponState* GetWeaponStateComponent() const { return WeaponStateComponent; }
};
