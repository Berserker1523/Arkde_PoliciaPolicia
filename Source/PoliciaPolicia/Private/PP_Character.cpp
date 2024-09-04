#include "PP_Character.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Camera/CameraComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "Components/PP_HealthComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Core/PP_GameMode.h"
#include "CharacterActionStates/PP_IdleState.h"
#include "CharacterActionStates/PP_MeleeState.h"
#include "CharacterActionStates/PP_WeaponState.h"
#include "Components/PP_MeleeCollider.h"
#include "CharacterActionStates/PP_CharacterActionsStateModel.h"
#include "Engine/World.h"

APP_Character::APP_Character()
{
	PrimaryActorTick.bCanEverTick = false;

	bIsRunning = false;
	bUseFirstPersonView = true;
	FPSCameraSocketName = "SCK_Camera";
	MeleeSocketName = "SCK_Melee";

	CharacterMovementComponent = GetCharacterMovement();
	walkSpeed = CharacterMovementComponent->MaxWalkSpeed;
	runSpeed = walkSpeed * 1.25f;

	FPSCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FPS_CameraComponent"));
	FPSCameraComponent->bUsePawnControlRotation = true;
	FPSCameraComponent->SetupAttachment(GetMesh(), FPSCameraSocketName);

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	SpringArmComponent->bUsePawnControlRotation = true;
	SpringArmComponent->SetupAttachment(RootComponent);

	TPSCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TPS_CameraComponent"));
	TPSCameraComponent->SetupAttachment(SpringArmComponent);

	HealthComponent = CreateDefaultSubobject<UPP_HealthComponent>(TEXT("HealthComponent"));

	IdleStateComponent = CreateDefaultSubobject<UPP_IdleState>(TEXT("IdleStateComponent"));
	MeleeStateComponent = CreateDefaultSubobject<UPP_MeleeState>(TEXT("MeleeStateComponent"));
	WeaponStateComponent = CreateDefaultSubobject<UPP_WeaponState>(TEXT("WeaponStateComponent"));

	MeleeColliderComponent = CreateDefaultSubobject<UPP_MeleeCollider>(TEXT("MeleeColliderComponent"));
	MeleeColliderComponent->SetupAttachment(GetMesh(), MeleeSocketName);

	CharacterActionsStateModelComponent = CreateDefaultSubobject<UPP_CharacterActionsStateModel>(TEXT("CharacterActionsStateModelComponent"));
}

void APP_Character::BeginPlay()
{
	Super::BeginPlay();
	GameMode = Cast<APP_GameMode>(GetWorld()->GetAuthGameMode());
	HealthComponent->OnHealthChangeDelegate.AddDynamic(this, &APP_Character::OnHealthChanged);
}

void APP_Character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &APP_Character::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &APP_Character::MoveRight);

	PlayerInputComponent->BindAxis("LookUp", this, &APP_Character::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookRight", this, &ACharacter::AddControllerYawInput);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAction("ChangeView", IE_Pressed, this, &APP_Character::SwitchView);
	PlayerInputComponent->BindAction("Run", IE_Pressed, this, &APP_Character::SwitchRunning);
}

FVector APP_Character::GetPawnViewLocation() const
{
	if (bUseFirstPersonView && IsValid(FPSCameraComponent))
		return FPSCameraComponent->GetComponentLocation();

	if (!bUseFirstPersonView && IsValid(TPSCameraComponent))
		return TPSCameraComponent->GetComponentLocation();

	return Super::GetPawnViewLocation();
}

void APP_Character::MoveForward(float value)
{
	//AddMovementInput(UKismetMathLibrary::GetForwardVector(GetActorRotation()) * value); the same than below
	AddMovementInput(GetActorForwardVector() * value);
}

void APP_Character::MoveRight(float value)
{
	AddMovementInput(GetActorRightVector() * value);
}

void APP_Character::AddControllerPitchInput(float value)
{
	Super::AddControllerPitchInput(bIsLookInverted ? -value : value);
}

void APP_Character::AddKey(FName NewKey)
{
	DoorKeys.Add(NewKey);
}

bool APP_Character::HasKey(FName Key)
{
	return DoorKeys.Contains(Key);
}

void APP_Character::SwitchView()
{
	bUseFirstPersonView = !bUseFirstPersonView;

	if (bUseFirstPersonView)
	{
		FPSCameraComponent->Activate();
		SpringArmComponent->Deactivate();
		TPSCameraComponent->Deactivate();
	}
	else
	{
		FPSCameraComponent->Deactivate();
		SpringArmComponent->Activate();
		TPSCameraComponent->Activate();
	}
}

void APP_Character::SwitchRunning()
{
	bIsRunning = !bIsRunning;
	CharacterMovementComponent->MaxWalkSpeed = bIsRunning ? runSpeed : walkSpeed;
}

void APP_Character::OnHealthChanged(UPP_HealthComponent* CurrentHealthComponent, AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	if (CurrentHealthComponent->IsDead() && IsValid(GameMode))
		GameMode->GameOver(this);
}
