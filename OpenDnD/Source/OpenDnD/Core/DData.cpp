// Fill out your copyright notice in the Description page of Project Settings.

#include "DData.h"

DData::DData()
{
}

DData::~DData()
{
}

// Build the load path
FString DData::BuildPath(FName FileName, FString Directory)
{
    FString LoadFilePath = FPaths::ConvertRelativePathToFull(FPaths::ProjectContentDir());
    LoadFilePath += "Data/";
    LoadFilePath += Directory;
    LoadFilePath += "/";
    LoadFilePath += FileName.ToString();
    LoadFilePath += ".json";
    
    return LoadFilePath;
}

// Load Resource
void DData::LoadResource(FName FileName, FDResourceStruct* Resource)
{
    if (FileName != NAME_None)
    {
        FString JsonString;
        FString LoadFilePath = BuildPath(FileName, "Resources");
        
        if (FPaths::FileExists(LoadFilePath))
        {
            FFileHelper::LoadFileToString(JsonString, *LoadFilePath);
            FJsonObjectConverter::JsonObjectStringToUStruct(JsonString, Resource, 0, 0);
        }
        else
        {
            UE_LOG(DErrorLog, Error, TEXT("Resource does not exist at %s!"), *LoadFilePath);
        }
    }
}

// Load Dialog
void DData::LoadDialog(FName FileName, FDDialogStruct* Dialog)
{
    if (FileName != NAME_None)
    {
        FString JsonString;
        FString LoadFilePath = BuildPath(FileName, "Dialogs");
        
        if (FPaths::FileExists(LoadFilePath))
        {
            FFileHelper::LoadFileToString(JsonString, *LoadFilePath);
            FJsonObjectConverter::JsonObjectStringToUStruct(JsonString, Dialog, 0, 0);
        }
        else
        {
            UE_LOG(DErrorLog, Error, TEXT("Dialog does not exist at %s!"), *LoadFilePath);
        }
    }
}

// Load Item
void DData::LoadItem(FName FileName, FDItemStruct* Item)
{
    if (FileName != NAME_None)
    {
        FString JsonString;
        FString LoadFilePath = BuildPath(FileName, "Items");
        
        if (FPaths::FileExists(LoadFilePath))
        {
            FFileHelper::LoadFileToString(JsonString, *LoadFilePath);
            FJsonObjectConverter::JsonObjectStringToUStruct(JsonString, Item, 0, 0);
        }
        else
        {
            UE_LOG(DErrorLog, Error, TEXT("Item does not exist at %s!"), *LoadFilePath);
        }
    }
}

// Load Person
void DData::LoadPerson(FName FileName, FDPersonStruct* Person)
{
    if (FileName != NAME_None)
    {
        FString JsonString;
        FString LoadFilePath = BuildPath(FileName, "Persons");
        
        if (FPaths::FileExists(LoadFilePath))
        {
            FFileHelper::LoadFileToString(JsonString, *LoadFilePath);
            FJsonObjectConverter::JsonObjectStringToUStruct(JsonString, Person, 0, 0);
        }
        else
        {
            UE_LOG(DErrorLog, Error, TEXT("Person does not exist at %s!"), *LoadFilePath);
        }
    }
}
