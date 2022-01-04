// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "PP_GameMode.generated.h"

class APP_Character;

/**
 * 
 */
UCLASS()
class POLICIAPOLICIA_API APP_GameMode : public AGameModeBase
{
	GENERATED_BODY()
	

public:

	UFUNCTION()
	void Victory(APP_Character* Character);

	UFUNCTION()
	void GameOver();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void BP_Victory(APP_Character* Character);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void BP_GameOver();
};
