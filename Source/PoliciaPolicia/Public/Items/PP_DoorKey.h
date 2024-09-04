#pragma once

#include "CoreMinimal.h"
#include "Items/PP_Item.h"
#include "PP_DoorKey.generated.h"

class UStaticMeshComponent;

/**
 * 
 */
UCLASS()
class POLICIAPOLICIA_API APP_DoorKey : public APP_Item
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* KeyMeshComponent;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Key")
	FName KeyTag;

protected:
	virtual void Pickup(APP_Character* PickupCharacter) override;

public:
	UFUNCTION(BlueprintCallable, Category = "Getter")
	FName GetKeyTag() const { return KeyTag; };

public:
	// Sets default values for this actor's properties
	APP_DoorKey();
};
