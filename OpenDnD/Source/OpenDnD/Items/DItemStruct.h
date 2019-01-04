// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Dialogs/DDialogStruct.h"

#include "DItemStruct.generated.h"

USTRUCT(BlueprintType)
struct FDLinkItemStruct
{
    GENERATED_USTRUCT_BODY()
public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
    FText name;
    
    UPROPERTY(BlueprintReadOnly, Category = "Item")
    FName uuid;
    
    FDLinkItemStruct()
    {
        name = FText();
        uuid = TEXT("");
    }
};

USTRUCT(BlueprintType)
struct FDItemStruct
{
    GENERATED_USTRUCT_BODY()
public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
    FText name;
    
    UPROPERTY(BlueprintReadOnly, Category = "Item")
    FName uuid;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
    uint8 currentDialog;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
    TArray<FDLinkDialogStruct> dialogs;
    
    FDItemStruct()
    {
        name = FText();
        uuid = TEXT("");
        currentDialog = 0;
        TArray<FDLinkDialogStruct> dialogs;
    }
};
