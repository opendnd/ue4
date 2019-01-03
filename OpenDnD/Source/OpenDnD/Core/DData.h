// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "OpenDnD.h"
#include <Object.h>
#include "JsonObjectConverter.h"
#include <Paths.h>
#include <FileHelper.h>
#include "Core/DResourceStruct.h"
#include "Dialogs/DDialogStruct.h"
#include "Items/DItemStruct.h"
#include "Persons/DPersonStruct.h"

/**
 * 
 */
class OPENDND_API DData
{
public:
	DData();
	~DData();
    
    // Build the path to load the file
    static FString BuildPath(FName FileName, FString Directory);
    
    // Load a generic resource
    UFUNCTION()
    static void LoadResource(FName FileName, FDResourceStruct* Resource);
    
    // Load a dialog
    UFUNCTION()
    static void LoadDialog(FName FileName, FDDialogStruct* Dialog);
    
    // Load an item
    UFUNCTION()
    static void LoadItem(FName FileName, FDItemStruct* Item);
    
    // Load a person
    UFUNCTION()
    static void LoadPerson(FName FileName, FDPersonStruct* Person);
};
