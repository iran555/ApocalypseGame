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
#include "Components/PanelWidget.h"
class UWidget;

#include "AGUIElementShared.generated.h"

//# This class is created in order to bring DRY policy to UIElements.
//! FunctionLibrary class; Inheritance is not allowed.
UCLASS(NotBlueprintable, NotBlueprintType)
class UAGUIElementShared final : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

public:
    //# Clone a widget with its children. This function not copying any transform to parent.
    //# First attach then call CopyTransform() to fully copying it.
    static UWidget* DeepClone(UWidget* Target, UPanelWidget* Parent);

    //# Try to cast and find the suitable slot and copy them from "From"
    static void CopyTransform(UPanelSlot* From, UPanelSlot* To);
};
