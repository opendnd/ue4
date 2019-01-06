// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Dialogs/DDialogStruct.h"

#include "DItemStruct.generated.h"

USTRUCT(BlueprintType)
struct FDLinkItemStruct
{
    GENERATED_USTRUCT_BODY()
public:
    UPROPERTY(BlueprintReadWrite, Category = "Item")
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
    UPROPERTY(BlueprintReadWrite, Category = "Item")
    FText name;
    
    UPROPERTY(BlueprintReadOnly, Category = "Item")
    FName uuid;
    
    UPROPERTY(BlueprintReadOnly, Category = "Item")
    int32 weight;
    
    UPROPERTY(BlueprintReadWrite, Category = "Item")
    TArray<FDLinkItemStruct> items;
    
    UPROPERTY(BlueprintReadWrite, Category = "Item")
    int32 currentDialog;
    
    UPROPERTY(BlueprintReadWrite, Category = "Item")
    TArray<FDLinkDialogStruct> dialogs;
    
    FDItemStruct()
    {
        name = FText();
        uuid = TEXT("");
        currentDialog = 0;
        TArray<FDLinkDialogStruct> dialogs;
    }
};
