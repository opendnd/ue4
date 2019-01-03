// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "DDialogStruct.generated.h"

USTRUCT(BlueprintType)
struct FDDialogStruct
{
    GENERATED_USTRUCT_BODY()
public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialog")
    FString name;
    
    UPROPERTY(BlueprintReadOnly, Category = "Dialog")
    FString uuid;
    
    FDDialogStruct()
    {};
};
