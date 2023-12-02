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
#include "InputMappingContext.h"
#include "InputAction.h"
#include "AGInput/AGInputHandlers.h"
#include "EnhancedInputSubsystems.h"

void AAGPlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();

    // input
    InputHandlers = NewObject<UAGInputHandlers>();
    InputHandlers->PlayerController = this;
    UpdateInputMode("OnFoot");
}

#pragma region Input

void AAGPlayerController::UpdateInputMode(const FName InputModeName)
{
    UE_LOG(LogAGAI, Log, TEXT("UpdateInputMode called. InputModeName: \"%s\""), *InputModeName.ToString())
    UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);
    UEnhancedInputLocalPlayerSubsystem* InputSystem = Cast<ULocalPlayer>(Player)->
        GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
    CurrentInputMode = InputModeName;

    // clear everything
    EnhancedInputComponent->ClearActionBindings();
    InputSystem->ClearAllMappings();

    // try to find the InputMappingContext by generated path.
    UInputMappingContext* InputMappingContext =
        Cast<UInputMappingContext>(FStringAssetReference(FString::Printf(
            TEXT("/Script/EnhancedInput.InputMappingContext'/Game/AGAI/Input/IMC_%s.IMC_%s'"),
            *InputModeName.ToString(), *InputModeName.ToString())).TryLoad());
    if (!InputMappingContext)
    {
        UE_LOG(
            LogAGAI, Error, TEXT("UpdateInputMode: Cant find the InputMappingContext with name \"IMC_%s\""),
            *InputModeName.ToString())
        return;
    }
    
    // check all mappings at InputMappingContext.
    TArray<FString> DoneActions = {};
    for (int32 i = 0; i < InputMappingContext->GetMappings().Num(); ++i)
    {
        // avoid running a action twice.
        if (FString ActionName = InputMappingContext->GetMapping(i).Action->GetName();
            !DoneActions.Contains(ActionName))
        {
            DoneActions.Add(ActionName);

            // try to load by generated generated path.
            const UInputAction* Action = Cast<UInputAction>(FStringAssetReference(FString::Printf(
                TEXT("/Script/EnhancedInput.InputAction'/Game/AGAI/Input/%s/%s.%s'"),
                *InputModeName.ToString(), *ActionName, *ActionName)).TryLoad());

            if (Action)
            {
                // try to find handler by name.
                FString CleanActionName = "";
                ActionName.Split("_", nullptr, &CleanActionName);
                CleanActionName.Split("_", &CleanActionName, nullptr);
                const FName FunctionName =
                    FName(FString::Printf(TEXT("%s_%s"), *InputModeName.ToString(), *CleanActionName));
                if (InputHandlers->FindFunction(FunctionName))
                {
                    EnhancedInputComponent->BindAction(
                        Action, ETriggerEvent::Triggered, InputHandlers, FunctionName);
                }
                else
                {
                    UE_LOG(
                        LogAGAI, Error,
                        TEXT("UpdateInputMode: Cant find the handler with name \"%s\""), *FunctionName.ToString())
                    return;
                }
            }
            else
            {
                UE_LOG(
                    LogAGAI, Error, TEXT("UpdateInputMode: Cant find the action with name \"%s\""), *ActionName)
                return;
            }
        }
    }

    // add the mapping context
    InputSystem->AddMappingContext(InputMappingContext, 0);
}

#pragma endregion Input
