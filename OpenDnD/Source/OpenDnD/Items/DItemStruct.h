// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "DItemStruct.generated.h"

USTRUCT(BlueprintType)
struct FDItemStruct
{
    GENERATED_USTRUCT_BODY()
public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
    FString name;
    
    UPROPERTY(BlueprintReadOnly, Category = "Item")
    FString uuid;
    
    FDItemStruct()
    {};
};
