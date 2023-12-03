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
struct FInputActionValue;
class AAGPlayerController;

#include "AGInputHandlers.generated.h"

//# This class holding input handlers.
//* All input modes must have there handlers registered hare.
//! FunctionLibrary class; Inheritance is not allowed.
UCLASS(NotBlueprintable, NotBlueprintType)
class UAGInputHandlers final : public UObject
{
    GENERATED_BODY()

public:
    UPROPERTY()
    AAGPlayerController* PlayerController = nullptr;

    //* Input handler naming format: {InputMode.Name}_{Action.Name}

    //# Direct move input. [W][A][S][D] in most games.
    //! Carry 2D data.
    UFUNCTION()
    void OnFoot_Move(const FInputActionValue& RawInput);

    //# Change the angel of view. [Mouse] in most games.
    //! Carry 2D data.
    UFUNCTION()
    void OnFoot_Look(const FInputActionValue& RawInput);
};
