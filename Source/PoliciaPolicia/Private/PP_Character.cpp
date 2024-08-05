#include "PP_Character.h"
#include "PoliciaPolicia.h"
#include "Weapons/PP_Weapon.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Camera/CameraComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "Animation/AnimInstance.h"
#include "Animation/AnimMontage.h"
#include "Components/PP_HealthComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
APP_Character::APP_Character()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bIsRunning = false;
	bIsDoingMelee = false;
	bCanUseWeapon = true;
	bUseFirstPersonView = true;
	FPSCameraSocketName = "SCK_Camera";
	MeleeSocketName = "SCK_Melee";
	MeleeDamage = 50.0f;
	MaxComboMultiplier = 4.0f;
	CurrentComboMultiplier = 1.0f;

	FPSCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FPS_CameraComponent"));
	FPSCameraComponent->bUsePawnControlRotation = true;
	FPSCameraComponent->SetupAttachment(GetMesh(), FPSCameraSocketName);

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	SpringArmComponent->bUsePawnControlRotation = true;
	SpringArmComponent->SetupAttachment(RootComponent);

	TPSCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TPS_CameraComponent"));
	TPSCameraComponent->SetupAttachment(SpringArmComponent);

	CharacterMovementComponent = GetCharacterMovement();
	walkSpeed = CharacterMovementComponent->MaxWalkSpeed;
	runSpeed = walkSpeed * 1.25f;

	MeleeDetectorComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("MeleeDetectorComponent"));
	MeleeDetectorComponent->SetupAttachment(GetMesh(), MeleeSocketName);
	MeleeDetectorComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
	MeleeDetectorComponent->SetCollisionResponseToChannel(COLLISION_ENEMY, ECR_Overlap);
	MeleeDetectorComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	HealthComponent = CreateDefaultSubobject<UPP_HealthComponent>(TEXT("HealthComponent"));
}

FVector APP_Character::GetPawnViewLocation() const
{
	if (IsValid(FPSCameraComponent) && bUseFirstPersonView)
		return FPSCameraComponent->GetComponentLocation();

	if (IsValid(TPSCameraComponent) && !bUseFirstPersonView)
		return TPSCameraComponent->GetComponentLocation();

	return Super::GetPawnViewLocation();
}

// Called when the game starts or when spawned
void APP_Character::BeginPlay()
{
	Super::BeginPlay();
	InitializeReferences();
	CreateInitialWeapon();
	MeleeDetectorComponent->OnComponentBeginOverlap.AddDynamic(this, &APP_Character::MakeMeleeDamage);
}

void APP_Character::InitializeReferences()
{
	if (IsValid(GetMesh()))
		MyAnimInstance = GetMesh()->GetAnimInstance();
}

// Called every frame
void APP_Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
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

void APP_Character::CreateInitialWeapon()
{
	if (IsValid(InitialWeaponClass))
	{
		CurrentWeapon = GetWorld()->SpawnActor<APP_Weapon>(InitialWeaponClass, GetActorLocation(), GetActorRotation());
		if (IsValid(CurrentWeapon))
		{
			CurrentWeapon->SetCharacterOwner(this);
			CurrentWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, FPSCameraSocketName);
		}
	}
}

void APP_Character::StartWeaponAction()
{
	if (!bCanUseWeapon)
		return;

	if (bIsRunning)
		SwitchRunning();

	if (IsValid(CurrentWeapon))
		CurrentWeapon->StartAction();
}

void APP_Character::StopWeaponAction()
{
	if (!bCanUseWeapon)
		return;

	if (IsValid(CurrentWeapon))
		CurrentWeapon->StopAction();
}

void APP_Character::StartMelee()
{
	if (bIsDoingMelee && !bCanMakeCombos)
		return;

	if (bCanMakeCombos)
	{
		if (bIsDoingMelee)
		{
			if (bIsComboEnable)
			{
				if (CurrentComboMultiplier < MaxComboMultiplier)
				{
					CurrentComboMultiplier++;
					SetComboEnable(false);
				}
				else
					return;
			}
			else
				return;
		}
	}

	if (IsValid(MyAnimInstance) && IsValid(MeleeMontage))
	{
		MyAnimInstance->Montage_Play(MeleeMontage);
		SetMeleeState(true);
	}
}

void APP_Character::StopMelee()
{
}

void APP_Character::MakeMeleeDamage(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (IsValid(OtherActor))
		UGameplayStatics::ApplyPointDamage(OtherActor, MeleeDamage * CurrentComboMultiplier, SweepResult.Location, SweepResult, GetInstigatorController(), this, nullptr);
}

// Called to bind functionality to input
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

	PlayerInputComponent->BindAction("WeaponAction", IE_Pressed, this, &APP_Character::StartWeaponAction);
	PlayerInputComponent->BindAction("WeaponAction", IE_Released, this, &APP_Character::StopWeaponAction);

	PlayerInputComponent->BindAction("Melee", IE_Pressed, this, &APP_Character::StartMelee);
	PlayerInputComponent->BindAction("Melee", IE_Released, this, &APP_Character::StopMelee);
}

void APP_Character::AddKey(FName NewKey)
{
	DoorKeys.Add(NewKey);
}

bool APP_Character::HasKey(FName Key)
{
	return DoorKeys.Contains(Key);
}

void APP_Character::SetMeleeDetectorCollision(ECollisionEnabled::Type NewCollisionState)
{
	MeleeDetectorComponent->SetCollisionEnabled(NewCollisionState);
}

void APP_Character::SetMeleeState(bool NewState)
{
	bIsDoingMelee = NewState;
	bCanUseWeapon = !NewState;
}

void APP_Character::SetComboEnable(bool NewState)
{
	bIsComboEnable = NewState;
}

void APP_Character::ResetCombo()
{
	SetComboEnable(false);
	CurrentComboMultiplier = 1.0f;
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
