// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Persons/DPersonCharacter.h"
#include "Dialogs/DDialogStruct.h"
#include "Items/DItemStruct.h"

#include "DPlayableCharacter.generated.h"

// Add delegates
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDialogStartDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDialogEndDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDialogNextDelegate, FDChoiceStruct, Choice);

/**
 * 
 */
UCLASS()
class OPENDND_API ADPlayableCharacter : public ADPersonCharacter
{
	GENERATED_BODY()
	
    /** Camera boom positioning the camera behind the character */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
    class USpringArmComponent* CameraBoom;
    
    /** Follow camera */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
    class UCameraComponent* FollowCamera;
public:
    ADPlayableCharacter();
    
    /** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
    float BaseTurnRate;
    
    /** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
    float BaseLookUpRate;
    
protected:
    
    /** Resets HMD orientation in VR. */
    void OnResetVR();
    
    /** Called for forwards/backward input */
    void MoveForward(float Value);
    
    /** Called for side to side input */
    void MoveRight(float Value);
    
    /**
     * Called via input to turn at a given rate.
     * @param Rate    This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
     */
    void TurnAtRate(float Rate);
    
    /**
     * Called via input to turn look up/down at a given rate.
     * @param Rate    This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
     */
    void LookUpAtRate(float Rate);
    
    /** Handler for when a touch input begins. */
    void TouchStarted(ETouchIndex::Type FingerIndex, FVector Location);
    
    /** Handler for when a touch input stops. */
    void TouchStopped(ETouchIndex::Type FingerIndex, FVector Location);
    
protected:
    // APawn interface
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
    // End of APawn interface
    
public:
    /** Returns CameraBoom subobject **/
    FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
    /** Returns FollowCamera subobject **/
    FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
    
    // Items
    UFUNCTION(BlueprintCallable, Category = "Item")
    void AddItem(FDLinkItemStruct Link);
    
    UFUNCTION(BlueprintCallable, Category = "Item")
    void AddItems(TArray<FDLinkItemStruct> Items);
    
    // Properties for the dialog
    UPROPERTY(BlueprintAssignable, Category = "Dialog")
    FDialogStartDelegate OnDialogStart;
    
    UPROPERTY(BlueprintAssignable, Category = "Dialog")
    FDialogEndDelegate OnDialogEnd;
    
    UPROPERTY(BlueprintAssignable, Category = "Dialog")
    FDialogNextDelegate OnDialogNext;
    
    UPROPERTY(BlueprintReadWrite, Category = "Dialog")
    AActor* InteractingActor;
    
    UPROPERTY(BlueprintReadWrite, Category = "Dialog")
    FDDialogStruct Dialog;
    
    UPROPERTY(BlueprintReadWrite, Category = "Dialog")
    FDResponseStruct DialogResponse;

    UPROPERTY(BlueprintReadWrite, Category = "Dialog")
    FDChoiceStruct DialogChoice1;
    
    UPROPERTY(BlueprintReadWrite, Category = "Dialog")
    FDChoiceStruct DialogChoice2;
    
    UPROPERTY(BlueprintReadWrite, Category = "Dialog")
    FDChoiceStruct DialogChoice3;
    
    UPROPERTY(BlueprintReadWrite, Category = "Dialog")
    FDChoiceStruct DialogChoice4;
    
    UPROPERTY(BlueprintReadWrite, Category = "Dialog")
    FDChoiceStruct DialogChoice5;
    
    UPROPERTY(BlueprintReadWrite, Category = "Dialog")
    FDChoiceStruct DialogChoice6;
    
    // Set current dialog
    UFUNCTION(BlueprintCallable, Category = "Dialog")
    void SetDialogPrompt();
    
    // Start dialog
    UFUNCTION(BlueprintCallable, Category = "Dialog")
    void StartDialog();
    
    // End dialog
    UFUNCTION(BlueprintCallable, Category = "Dialog")
    void EndDialog();
    
    // Next dialog
    UFUNCTION(BlueprintCallable, Category = "Dialog")
    void NextDialog(FName ChoiceName);
    void NextDialogWithChoice(FDChoiceStruct Choice);
    
    // Goto response
    UFUNCTION(BlueprintCallable, Category = "Dialog")
    void GoToResponse(int32 currentResponse);
};
