/* Copyright (C) 2023 Iran555 iran555@proton.me
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *         http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License. */

#include "AGAI/Public/AGControllers/AGPlayerController.h"
#include "AGAI/AGAI.h"

// input
#include "EnhancedInputComponent.h"
#include "InputCoreTypes.h"
#include "InputAction.h"

void AAGPlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();

    UpdateInputMode(); // init current InputMode
}

#pragma region Input

#define BIND_INPUT(Action, Handel)\
    if (!Action.IsNull())\
    {\
        EnhancedInputComponent->BindAction(\
            Action.LoadSynchronous(), ETriggerEvent::Triggered,\
            this, &AAGPlayerController::Handel);\
    }\
    else UE_LOG(LogAGAI, Error, TEXT("AGPlayerController: %s is not setted"), *FString(#Action));
void AAGPlayerController::UpdateInputMode()
{
    UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);

    // clear everything
    EnhancedInputComponent->ClearActionBindings();

    // bind as InputMode order
    switch (InputMode)
    {
    case EAGPlayerController_InputMode::OnFoot:
        BIND_INPUT(Move_InputAction, Move_InputHandel);
        BIND_INPUT(Look_InputAction, Look_InputHandel);
        break;
    default:
        BIND_INPUT(Move_InputAction, Move_InputHandel);
        BIND_INPUT(Look_InputAction, Look_InputHandel);
        UE_LOG(LogAGAI, Error, TEXT("AGPlayerController: an input mode is not defined in UpdateInputMode"))
        break;
    }
}
#undef BIND_INPUT

// ReSharper disable CppMemberFunctionMayBeConst

void AAGPlayerController::Move_InputHandel(const FInputActionValue& RawInput)
{
    const FVector2D InputValue = RawInput.Get<FVector2D>();
    APawn* PlayerPawn = GetPawn();

    PlayerPawn->AddMovementInput(PlayerPawn->GetActorForwardVector(), InputValue.X);
    PlayerPawn->AddMovementInput(PlayerPawn->GetActorRightVector(), InputValue.Y);
}

void AAGPlayerController::Look_InputHandel(const FInputActionValue& RawInput)
{
    const FVector2D InputValue = RawInput.Get<FVector2D>();
    APawn* PlayerPawn = GetPawn();

    PlayerPawn->AddControllerYawInput(InputValue.X);
    PlayerPawn->AddControllerPitchInput(InputValue.Y);
}

// ReSharper restore CppMemberFunctionMayBeConst
#pragma endregion Input
