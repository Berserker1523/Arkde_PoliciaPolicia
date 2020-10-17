// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PP_Platform.generated.h"

class UStaticMeshComponent;

UCLASS()
class POLICIAPOLICIA_API APP_Platform : public AActor
{
	GENERATED_BODY()

protected:

	UPROPERTY(VisibleAnywhere, Category = "Components")
	USceneComponent* CustomRootComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* PlatformMeshComponent;
	
protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Platform")
	bool bIsGoingUp;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Platform")
	float Speed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Platform")
	float MinHeight;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Platform")
	float MaxHeight;

public:	
	// Sets default values for this actor's properties
	APP_Platform();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UFUNCTION(BlueprintCallable, Category = "Movement")
	void Move();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
