// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Core/DData.h"
#include "DItemStruct.h"

#include "DItem.generated.h"

UCLASS()
class OPENDND_API ADItem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADItem();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

    // Property for the file name
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
    FName FileName;
    
    // Property for the data
    UPROPERTY(BlueprintReadWrite, Category = "Item")
    FDItemStruct Item;
    
    // Load the data from the file name
    UFUNCTION(BlueprintCallable, Category = "Item")
    void LoadData();
    
    // Get current dialog
    UFUNCTION(BlueprintCallable, Category = "Item")
    FDDialogStruct GetCurrentDialog();
    
    // Increment the dialog
    UFUNCTION(BlueprintCallable, Category = "Item")
    void IncrementDialog();
};
