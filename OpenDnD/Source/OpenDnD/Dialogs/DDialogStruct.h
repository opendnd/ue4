// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "DDialogStruct.generated.h"

USTRUCT(BlueprintType)
struct FDResponseStruct
{
    GENERATED_USTRUCT_BODY()
public:
    UPROPERTY(BlueprintReadOnly, Category = "Dialog")
    FText text;
    
    UPROPERTY(BlueprintReadOnly, Category = "Dialog")
    int32 prompt;
    
    UPROPERTY(BlueprintReadOnly, Category = "Dialog")
    TArray<FName> triggers;
    
    FDResponseStruct()
    {
        text = FText();
        prompt = -1;
        TArray<FName> triggers;
    }
};

USTRUCT(BlueprintType)
struct FDChoiceStruct
{
    GENERATED_USTRUCT_BODY()
public:
    UPROPERTY(BlueprintReadOnly, Category = "Dialog")
    FText text;
    
    UPROPERTY(BlueprintReadOnly, Category = "Dialog")
    int32 response;
    
    UPROPERTY(BlueprintReadOnly, Category = "Dialog")
    TArray<FName> triggers;
    
    FDChoiceStruct()
    {
        text = FText();
        response = -1;
        TArray<FName> triggers;
    }
};

USTRUCT(BlueprintType)
struct FDPromptStruct
{
    GENERATED_USTRUCT_BODY()
public:
    UPROPERTY(BlueprintReadOnly, Category = "Dialog")
    TArray<FDChoiceStruct> choices;
    
    FDPromptStruct()
    {
        TArray<FDChoiceStruct> choices;
    }
};

USTRUCT(BlueprintType)
struct FDLinkDialogStruct
{
    GENERATED_USTRUCT_BODY()
public:
    UPROPERTY(BlueprintReadWrite, Category = "Dialog")
    FText name;
    
    UPROPERTY(BlueprintReadOnly, Category = "Dialog")
    FName uuid;
    
    FDLinkDialogStruct()
    {
        name = FText();
        uuid = TEXT("");
    }
};

USTRUCT(BlueprintType)
struct FDDialogStruct
{
    GENERATED_USTRUCT_BODY()
public:
    UPROPERTY(BlueprintReadWrite, Category = "Dialog")
    FText name;
    
    UPROPERTY(BlueprintReadOnly, Category = "Dialog")
    FName uuid;
    
    UPROPERTY(BlueprintReadWrite, Category = "Dialog")
    int32 currentResponse;
    
    UPROPERTY(BlueprintReadOnly, Category = "Dialog")
    TArray<FDResponseStruct> responses;
    
    UPROPERTY(BlueprintReadOnly, Category = "Dialog")
    TArray<FDPromptStruct> prompts;
    
    FDDialogStruct()
    {
        name = FText();
        uuid = TEXT("");
        currentResponse = 0;
        TArray<FDResponseStruct> responses;
        TArray<FDPromptStruct> prompts;
    }
};
