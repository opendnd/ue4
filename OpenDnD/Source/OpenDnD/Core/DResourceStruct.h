// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "DResourceStruct.generated.h"

USTRUCT(BlueprintType)
struct FDLinkResourceStruct
{
    GENERATED_USTRUCT_BODY()
public:
    UPROPERTY(BlueprintReadWrite, Category = "Resource")
    FText name;
    
    UPROPERTY(BlueprintReadOnly, Category = "Resource")
    FName uuid;
    
    FDLinkResourceStruct()
    {
        name = FText();
        uuid = TEXT("");
    }
};

USTRUCT(BlueprintType)
struct FDResourceStruct
{
    GENERATED_USTRUCT_BODY()
public:
    UPROPERTY(BlueprintReadWrite, Category = "Resource")
    FText name;
    
    UPROPERTY(BlueprintReadOnly, Category = "Resource")
    FName uuid;
    
    FDResourceStruct()
    {
        name = FText();
        uuid = TEXT("");
    }
};
