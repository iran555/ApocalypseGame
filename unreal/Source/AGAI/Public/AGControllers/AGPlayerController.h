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

#pragma once
#include "CoreMinimal.h"
class UAGInputHandlers;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

#include "AGPlayerController.generated.h"

//# A controller is created to control a AGHuman with player input.
//! Abstract class; Inheritance is allowed only from BP.
UCLASS(Abstract, Blueprintable, DisplayName="Player Controller(AG)")
class AAGPlayerController : public APlayerController
{
    GENERATED_BODY()

public:
    //~ APlayerController
    virtual void SetupInputComponent() override;
    //~ End APlayerController

#pragma region Input

protected:
    //# input mode is define what and how input handled.
    //! To change call "UpdateInputMode".
    UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category="Input")
    FName CurrentInputMode = "None";

public:
    //# class that holds the handlers.
    UPROPERTY(Transient)
    UAGInputHandlers* InputHandlers;

    //# Change input mode.
    void UpdateInputMode(FName InputModeName);

#pragma endregion Input
};
