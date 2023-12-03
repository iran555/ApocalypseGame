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
#include "Blueprint/UserWidget.h"

#include "AGProceduralWidget.generated.h"

//! Reserved for "UAGProceduralWidget::Update".
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FAGProceduralWidget_Update);

//# Base class for every procedural widget in game.
//! Abstract class; Inheritance is allowed only from cpp.
UCLASS(NotBlueprintable, Abstract)
class AGUI_API UAGProceduralWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    //# Update the elements inside the widget with data.
    UPROPERTY(BlueprintAssignable)
    FAGProceduralWidget_Update Update = {};
};

//! Reserved for "UAGProceduralWidget_Mini::InputHandel_NavUp".
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FAGProceduralWidgetMini_InputHandel);

//# Mini UI in semi-interactable means user have 3 keys assigned to and a 1 direction navigator.
//! Abstract class; Inheritance is allowed only from Cpp.
UCLASS(NotBlueprintable, Abstract)
class AGUI_API UAGProceduralWidget_Mini : public UAGProceduralWidget
{
    GENERATED_BODY()

public:
    UPROPERTY(BlueprintAssignable)
    FAGProceduralWidgetMini_InputHandel InputHandel_NavUp = {};
    UPROPERTY(BlueprintAssignable)
    FAGProceduralWidgetMini_InputHandel InputHandel_NavDown = {};

    UPROPERTY(BlueprintAssignable)
    FAGProceduralWidgetMini_InputHandel InputHandel_Action0 = {};
    UPROPERTY(BlueprintAssignable)
    FAGProceduralWidgetMini_InputHandel InputHandel_Action1 = {};
    UPROPERTY(BlueprintAssignable)
    FAGProceduralWidgetMini_InputHandel InputHandel_Action2 = {};
};

//# This type of UI is full UI. when user interact with this type of UI they cant move.
//! Abstract class; Inheritance is allowed only from Cpp.
UCLASS(NotBlueprintable, Abstract)
class AGUI_API UAGProceduralWidget_Full : public UAGProceduralWidget
{
    GENERATED_BODY()
};
