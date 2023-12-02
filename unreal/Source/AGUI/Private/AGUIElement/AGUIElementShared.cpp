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

#include "AGUIElement/AGUIElementShared.h"

#include "Components/CanvasPanelSlot.h"
#include "Components/PanelWidget.h"
#include "Components/ScrollBoxSlot.h"
#include "Components/UniformGridSlot.h"

UWidget* UAGUIElementShared::DeepClone(UWidget* Target, UPanelWidget* Parent)
{
    // duplicate the parent
    UWidget* NewWidget = DuplicateObject<UWidget>(Target, Parent);

    if (UPanelWidget* NewWidgetAsPanelWidget = Cast<UPanelWidget>(NewWidget); NewWidgetAsPanelWidget)
    {
        // remove references to target
        for (UPanelSlot* i : NewWidgetAsPanelWidget->GetSlots()) i->Content = nullptr;
        NewWidgetAsPanelWidget->ClearChildren();

        // create new children
        const UPanelWidget* TargetAsPanelWidget = Cast<UPanelWidget>(Target);
        for (int i = 0; i < TargetAsPanelWidget->GetChildrenCount(); ++i)
        {
            UWidget* NewChild = DeepClone(TargetAsPanelWidget->GetChildAt(i), Parent);
            UPanelSlot* NewChildSlot = NewWidgetAsPanelWidget->AddChild(NewChild);

            CopyTransform(TargetAsPanelWidget->GetChildAt(i)->Slot, NewChildSlot);
        }
    }
    return NewWidget;
}

void UAGUIElementShared::CopyTransform(UPanelSlot* From, UPanelSlot* To)
{
    if (UCanvasPanelSlot* AsCanvasPanelSlot = Cast<UCanvasPanelSlot>(To); IsValid(AsCanvasPanelSlot))
    {
        const UCanvasPanelSlot* Slot = Cast<UCanvasPanelSlot>(From);
        AsCanvasPanelSlot->SetAlignment(Slot->GetAlignment());
        AsCanvasPanelSlot->SetLayout(Slot->GetLayout());
    }
    else if (UScrollBoxSlot* AsScrollBoxSlot = Cast<UScrollBoxSlot>(To); IsValid(AsScrollBoxSlot))
    {
        const UScrollBoxSlot* Slot = Cast<UScrollBoxSlot>(From);
        AsScrollBoxSlot->SetSize(Slot->GetSize());
        AsScrollBoxSlot->SetPadding(Slot->GetPadding());
        AsScrollBoxSlot->SetHorizontalAlignment(Slot->GetHorizontalAlignment());
        AsScrollBoxSlot->SetVerticalAlignment(Slot->GetVerticalAlignment());
    }
    else if (UUniformGridSlot* AsGridSlot = Cast<UUniformGridSlot>(To); IsValid(AsGridSlot))
    {
        const UUniformGridSlot* Slot = Cast<UUniformGridSlot>(From);
        AsGridSlot->SetRow(Slot->GetRow());
        AsGridSlot->SetColumn(Slot->GetColumn());
        AsGridSlot->SetHorizontalAlignment(Slot->GetHorizontalAlignment());
        AsGridSlot->SetVerticalAlignment(Slot->GetVerticalAlignment());
    }
}
