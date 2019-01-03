// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "DPersonStruct.generated.h"

USTRUCT(BlueprintType)
struct FDPersonStruct
{
    GENERATED_USTRUCT_BODY()
public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Person")
    FString name;
    
    UPROPERTY(BlueprintReadOnly, Category = "Person")
    FString uuid;
    
    FDPersonStruct()
    {};
};
