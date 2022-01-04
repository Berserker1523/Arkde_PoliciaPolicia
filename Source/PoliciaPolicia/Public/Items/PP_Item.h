// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PP_Item.generated.h"

class USphereComponent;
class APP_Character;

UCLASS()
class POLICIAPOLICIA_API APP_Item : public AActor
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USphereComponent* MainColliderComponent;

public:	
	// Sets default values for this actor's properties
	APP_Item();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void Pickup(APP_Character* PickupCharacter);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Item")
	void BP_Pickup(APP_Character* PickupCharacter);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void NotifyActorBeginOverlap(AActor* otherActor) override;
};
