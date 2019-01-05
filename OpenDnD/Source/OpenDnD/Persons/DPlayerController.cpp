// Fill out your copyright notice in the Description page of Project Settings.

#include "DPlayerController.h"

void ADPlayerController::ShowMouse()
{
    SetIgnoreMoveInput(true);
    bShowMouseCursor = true;
    bEnableClickEvents = true;
    bEnableMouseOverEvents = true;
    SetInputMode(FInputModeUIOnly());
}

void ADPlayerController::HideMouse()
{
    SetIgnoreMoveInput(false);
    bShowMouseCursor = false;
    bEnableClickEvents = false;
    bEnableMouseOverEvents = false;
    SetInputMode(FInputModeGameOnly());
}
