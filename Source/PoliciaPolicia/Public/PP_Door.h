#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PP_Door.generated.h"

class USceneComponent;
class UStaticMeshComponent;
class UBoxComponent;

UCLASS()
class POLICIAPOLICIA_API APP_Door : public AActor
{
	GENERATED_BODY()

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USceneComponent* CustomRootComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* DoorFrameComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* DoorComponent;

	UPROPERTY(Visibleanywhere, BlueprintReadOnly, Category = "Components")
	UBoxComponent* KeyZoneColliderComponent;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Door")
	float OpenAngle;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Door")
	bool bIsOpen;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Door")
	FName DoorTag;

public:
	APP_Door();

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void CheckKeyFromPlayer(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "My Door")
	void BP_OpenDoor();

public:
	void OpenDoor();
};
