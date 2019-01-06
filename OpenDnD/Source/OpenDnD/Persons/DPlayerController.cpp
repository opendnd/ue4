// Fill out your copyright notice in the Description page of Project Settings.

#include "DPlayerController.h"

void ADPlayerController::ShowMouse()
{
    SetIgnoreMoveInput(true);
    SetIgnoreLookInput(true);
    bShowMouseCursor = true;
    bEnableClickEvents = true;
    bEnableMouseOverEvents = true;
}

void ADPlayerController::HideMouse()
{
    SetIgnoreMoveInput(false);
    SetIgnoreLookInput(false);
    bShowMouseCursor = false;
    bEnableClickEvents = false;
    bEnableMouseOverEvents = false;    
}
