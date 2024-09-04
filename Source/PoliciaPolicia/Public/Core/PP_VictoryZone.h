#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PP_VictoryZone.generated.h"

class UBoxComponent;
class APP_GameMode;

UCLASS()
class POLICIAPOLICIA_API APP_VictoryZone : public AActor
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UBoxComponent* VictoryZoneComponent;

protected:
	APP_GameMode* GameModeReference;

public:
	APP_VictoryZone();

protected:
	virtual void BeginPlay() override;

public:
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
};
