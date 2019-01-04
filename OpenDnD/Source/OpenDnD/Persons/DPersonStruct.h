// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Dialogs/DDialogStruct.h"

#include "DPersonStruct.generated.h"

USTRUCT(BlueprintType)
struct FDLinkPersonStruct
{
    GENERATED_USTRUCT_BODY()
public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Person")
    FText name;
    
    UPROPERTY(BlueprintReadOnly, Category = "Person")
    FName uuid;

    FDLinkPersonStruct()
    {
        name = FText();
        uuid = TEXT("");
    }
};


USTRUCT(BlueprintType)
struct FDPersonStruct
{
    GENERATED_USTRUCT_BODY()
public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Person")
    FText name;
    
    UPROPERTY(BlueprintReadOnly, Category = "Person")
    FName uuid;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Person")
    uint8 currentDialog;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Person")
    TArray<FDLinkDialogStruct> dialogs;
    
    FDPersonStruct()
    {
        name = FText();
        uuid = TEXT("");
        currentDialog = 0;
        TArray<FDLinkDialogStruct> dialogs;
    }
};
