// Fill out your copyright notice in the Description page of Project Settings.


#include "PP_GameMode.h"
#include "PP_Character.h"

void APP_GameMode::Victory(APP_Character* Character)
{
	Character->DisableInput(nullptr);
	BP_Victory(Character);
}

void APP_GameMode::GameOver()
{
	BP_GameOver();
}