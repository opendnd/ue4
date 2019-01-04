// Fill out your copyright notice in the Description page of Project Settings.

#include "DPersonCharacter.h"

// Sets default values
ADPersonCharacter::ADPersonCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ADPersonCharacter::BeginPlay()
{
	Super::BeginPlay();
    LoadData();
}

// Called every frame
void ADPersonCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ADPersonCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

// Called to load the data
void ADPersonCharacter::LoadData()
{
    DData::LoadPerson(FileName, &Person);
}

// Get current dialog
FDDialogStruct ADPersonCharacter::GetCurrentDialog()
{
    FDDialogStruct Dialog;
    if (Person.dialogs.Num() > 0)
    {
        FDLinkDialogStruct Link = Person.dialogs[Person.currentDialog];
        DData::LoadDialog(Link.uuid, &Dialog);
    }
    
    return Dialog;
}
