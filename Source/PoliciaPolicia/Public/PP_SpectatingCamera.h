#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PP_SpectatingCamera.generated.h"

class UStaticMeshComponent;

UCLASS()
class POLICIAPOLICIA_API APP_SpectatingCamera : public AActor
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* SpectatingCameraComponent;

public:
	APP_SpectatingCamera();

};
