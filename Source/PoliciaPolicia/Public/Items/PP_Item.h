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
	APP_Item();

protected:

	virtual void Pickup(APP_Character* PickupCharacter);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Item")
	void BP_Pickup(APP_Character* PickupCharacter);

public:
	virtual void NotifyActorBeginOverlap(AActor* otherActor) override;
};
