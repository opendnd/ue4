// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Core/DData.h"
#include "DPersonStruct.h"
#include "Dialogs/DDialogStruct.h"

#include "DPersonCharacter.generated.h"

UCLASS()
class OPENDND_API ADPersonCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ADPersonCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;
    
    // Called to bind functionality to input
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

    // Property for the file name
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Person")
    FName FileName;
    
    // Property for the data
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Person")
    FDPersonStruct Person;
    
    // Load the data from the file name
    UFUNCTION(BlueprintCallable, Category = "Person")
    void LoadData();
    
    // Get current dialog
    UFUNCTION(BlueprintCallable, Category = "Person")
    FDDialogStruct GetCurrentDialog();
};
