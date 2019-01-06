// Fill out your copyright notice in the Description page of Project Settings.

#include "DPlayableCharacter.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "DPlayerController.h"
#include <EngineGlobals.h>
#include <Runtime/Engine/Classes/Engine/Engine.h>
#include <Runtime/Core/Public/Misc/OutputDeviceDebug.h>

//////////////////////////////////////////////////////////////////////////
// ADPlayableCharacter

ADPlayableCharacter::ADPlayableCharacter()
{
    // Set size for collision capsule
    GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
    
    // set our turn rates for input
    BaseTurnRate = 45.f;
    BaseLookUpRate = 45.f;
    
    // Don't rotate when the controller rotates. Let that just affect the camera.
    bUseControllerRotationPitch = false;
    bUseControllerRotationYaw = false;
    bUseControllerRotationRoll = false;
    
    // Configure character movement
    GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...
    GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
    GetCharacterMovement()->JumpZVelocity = 600.f;
    GetCharacterMovement()->AirControl = 0.2f;
    
    // Create a camera boom (pulls in towards the player if there is a collision)
    CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
    CameraBoom->SetupAttachment(RootComponent);
    CameraBoom->TargetArmLength = 300.0f; // The camera follows at this distance behind the character
    CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller
    
    // Create a follow camera
    FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
    FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
    FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm
    
    // Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character)
    // are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)
}

//////////////////////////////////////////////////////////////////////////
// Input

void ADPlayableCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
    // Set up gameplay key bindings
    check(PlayerInputComponent);
    PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
    PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
    
    PlayerInputComponent->BindAxis("MoveForward", this, &ADPlayableCharacter::MoveForward);
    PlayerInputComponent->BindAxis("MoveRight", this, &ADPlayableCharacter::MoveRight);
    
    // We have 2 versions of the rotation bindings to handle different kinds of devices differently
    // "turn" handles devices that provide an absolute delta, such as a mouse.
    // "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
    PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
    PlayerInputComponent->BindAxis("TurnRate", this, &ADPlayableCharacter::TurnAtRate);
    PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
    PlayerInputComponent->BindAxis("LookUpRate", this, &ADPlayableCharacter::LookUpAtRate);
    
    // handle touch devices
    PlayerInputComponent->BindTouch(IE_Pressed, this, &ADPlayableCharacter::TouchStarted);
    PlayerInputComponent->BindTouch(IE_Released, this, &ADPlayableCharacter::TouchStopped);
    
    // VR headset functionality
    PlayerInputComponent->BindAction("ResetVR", IE_Pressed, this, &ADPlayableCharacter::OnResetVR);
}


void ADPlayableCharacter::OnResetVR()
{
    UHeadMountedDisplayFunctionLibrary::ResetOrientationAndPosition();
}

void ADPlayableCharacter::TouchStarted(ETouchIndex::Type FingerIndex, FVector Location)
{
    Jump();
}

void ADPlayableCharacter::TouchStopped(ETouchIndex::Type FingerIndex, FVector Location)
{
    StopJumping();
}

void ADPlayableCharacter::TurnAtRate(float Rate)
{
    // calculate delta for this frame from the rate information
    AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void ADPlayableCharacter::LookUpAtRate(float Rate)
{
    // calculate delta for this frame from the rate information
    AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void ADPlayableCharacter::MoveForward(float Value)
{
    if ((Controller != NULL) && (Value != 0.0f))
    {
        // find out which way is forward
        const FRotator Rotation = Controller->GetControlRotation();
        const FRotator YawRotation(0, Rotation.Yaw, 0);
        
        // get forward vector
        const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
        AddMovementInput(Direction, Value);
    }
}

void ADPlayableCharacter::MoveRight(float Value)
{
    if ( (Controller != NULL) && (Value != 0.0f) )
    {
        // find out which way is right
        const FRotator Rotation = Controller->GetControlRotation();
        const FRotator YawRotation(0, Rotation.Yaw, 0);
        
        // get right vector
        const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
        // add movement in that direction
        AddMovementInput(Direction, Value);
    }
}

//////////////////////////////////////////////////////////////////////////
// Items
void ADPlayableCharacter::AddItem(FDLinkItemStruct Link)
{
    Person.items.Add(Link);
}

void ADPlayableCharacter::AddItems(TArray<FDLinkItemStruct> Items)
{
    if (Items.Num() > 0)
    {
        for (auto& Link : Items)
        {
            AddItem(Link);
        }
    }
}

//////////////////////////////////////////////////////////////////////////
// Dialog
void ADPlayableCharacter::SetDialogPrompt()
{
    if (Dialog.responses.Num() > Dialog.currentResponse)
    {
        FDResponseStruct Response = Dialog.responses[Dialog.currentResponse];
        DialogResponse = Response;
        
        if (Dialog.prompts.Num() > Response.prompt)
        {
            FDPromptStruct Prompt = Dialog.prompts[Response.prompt];
            
            if (Prompt.choices.Num() > 0)
            {
                DialogChoice1 = Prompt.choices[0];
            }
            else
            {
                DialogChoice1 = FDChoiceStruct();
            }
            
            if (Prompt.choices.Num() > 1)
            {
                DialogChoice2 = Prompt.choices[1];
            }
            else
            {
                DialogChoice2 = FDChoiceStruct();
            }
            
            if (Prompt.choices.Num() > 2)
            {
                DialogChoice3 = Prompt.choices[2];
            }
            else
            {
                DialogChoice3 = FDChoiceStruct();
            }
            
            if (Prompt.choices.Num() > 3)
            {
                DialogChoice4 = Prompt.choices[3];
            }
            else
            {
                DialogChoice4 = FDChoiceStruct();
            }
            
            if (Prompt.choices.Num() > 4)
            {
                DialogChoice5 = Prompt.choices[4];
            }
            else
            {
                DialogChoice5 = FDChoiceStruct();
            }
            
            if (Prompt.choices.Num() > 5)
            {
                DialogChoice6 = Prompt.choices[5];
            }
            else
            {
                DialogChoice6 = FDChoiceStruct();
            }
        }
    }
}

void ADPlayableCharacter::StartDialog()
{
    OnDialogStart.Broadcast();
    
    ADPlayerController* PlayerController = Cast<ADPlayerController>(Controller);
    
    if (PlayerController != NULL)
    {
        PlayerController->ShowMouse();
        PlayerController->SetInputMode(FInputModeUIOnly());
    }
}

void ADPlayableCharacter::EndDialog()
{
    OnDialogEnd.Broadcast();

    ADPlayerController* PlayerController = Cast<ADPlayerController>(Controller);

    if (PlayerController != NULL)
    {
        PlayerController->HideMouse();
        PlayerController->SetInputMode(FInputModeGameOnly());
    }
}

void ADPlayableCharacter::NextDialog(FName ChoiceName)
{
    if (ChoiceName == TEXT("1"))
    {
        NextDialogWithChoice(DialogChoice1);
    }
    else if (ChoiceName == TEXT("2"))
    {
        NextDialogWithChoice(DialogChoice2);
    }
    else if (ChoiceName == TEXT("3"))
    {
        NextDialogWithChoice(DialogChoice3);
    }
    else if (ChoiceName == TEXT("4"))
    {
        NextDialogWithChoice(DialogChoice4);
    }
    else if (ChoiceName == TEXT("5"))
    {
        NextDialogWithChoice(DialogChoice5);
    }
    else if (ChoiceName == TEXT("6"))
    {
        NextDialogWithChoice(DialogChoice6);
    }
}

void ADPlayableCharacter::NextDialogWithChoice(FDChoiceStruct Choice)
{
    OnDialogNext.Broadcast(Choice);

    // First check for triggers we can execute
    if (Choice.triggers.Num() > 0)
    {
        for (auto& Trigger : Choice.triggers)
        {
            UE_LOG(DLog, Log, TEXT("Calling trigger %s"), *Trigger.ToString());
            
            FOutputDeviceDebug debug;
            InteractingActor->CallFunctionByNameWithArguments(*Trigger.ToString(), debug, this, true);
        }
    }
    // Next check for another response
    else if (Choice.response > -1)
    {
        Dialog.currentResponse = Choice.response;
        SetDialogPrompt();
    }
    // Otherwise end the dialog
    else
    {
        EndDialog();
    }
}

// Goto response
void ADPlayableCharacter::GoToResponse(int32 currentResponse)
{
    Dialog.currentResponse = currentResponse;
    SetDialogPrompt();
}
