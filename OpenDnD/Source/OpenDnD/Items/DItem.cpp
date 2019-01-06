// Fill out your copyright notice in the Description page of Project Settings.

#include "DItem.h"

// Sets default values
ADItem::ADItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ADItem::BeginPlay()
{
	Super::BeginPlay();
    LoadData();
}

// Called every frame
void ADItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to load the data
void ADItem::LoadData()
{
    DData::LoadItem(FileName, &Item);
}

// Get current dialog
FDDialogStruct ADItem::GetCurrentDialog()
{
    FDDialogStruct Dialog;
    if (Item.dialogs.Num() > 0)
    {
        FDLinkDialogStruct Link = Item.dialogs[Item.currentDialog];
        DData::LoadDialog(Link.uuid, &Dialog);
    }
    else
    {
        UE_LOG(DErrorLog, Error, TEXT("No dialogs found"));
    }
    
    return Dialog;
}

// Increment the dialog
void ADItem::IncrementDialog()
{
    // TODO: make sure you can't go passed the total available
    Item.currentDialog += 1;
}
