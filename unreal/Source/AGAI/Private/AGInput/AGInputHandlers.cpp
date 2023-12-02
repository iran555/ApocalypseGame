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

#include "AGAI/Public/AGInput/AGInputHandlers.h"

#include "InputActionValue.h"
#include "AGControllers/AGPlayerController.h"

// ReSharper disable CppMemberFunctionMayBeConst

void UAGInputHandlers::OnFoot_Move(const FInputActionValue& RawInput)
{
    const FVector2D InputValue = RawInput.Get<FVector2D>();
    APawn* PlayerPawn = PlayerController->GetPawn();

    PlayerPawn->AddMovementInput(PlayerPawn->GetActorForwardVector(), InputValue.X);
    PlayerPawn->AddMovementInput(PlayerPawn->GetActorRightVector(), InputValue.Y);
}

void UAGInputHandlers::OnFoot_Look(const FInputActionValue& RawInput)
{
    const FVector2D InputValue = RawInput.Get<FVector2D>();
    APawn* PlayerPawn = PlayerController->GetPawn();

    PlayerPawn->AddControllerYawInput(InputValue.X);
    PlayerPawn->AddControllerPitchInput(InputValue.Y);
}

// ReSharper restore CppMemberFunctionMayBeConst
