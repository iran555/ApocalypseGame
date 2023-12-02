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

#include "AGUIElement/AGDynamicGrid.h"

#include "AGUIElement/AGUIElementShared.h"
#include "Components/PanelWidget.h"
#include "Components/CanvasPanel.h"
#include "Components/UniformGridSlot.h"

void UAGDynamicGrid::Setup() const
{
    // asserts
    check(TemplateItem);

    // hide template
    GetChildAt(0)->SetVisibility(ESlateVisibility::Collapsed);
}

void UAGDynamicGrid::RefreshGrid() const
{
    for (int32 i = 1; i < GetChildrenCount(); ++i)
    {
        if (GetChildAt(i)->GetVisibility() != ESlateVisibility::Collapsed) break;
        UUniformGridSlot* ChildSlot = Cast<UUniformGridSlot>(GetChildAt(i)->Slot);
        ChildSlot->SetRow((i % RowCount) - 1);
        ChildSlot->SetColumn(i / RowCount);
    }
}

void UAGDynamicGrid::Update(const int32 RequiredItems)
{
    // update current items
    for (int32 i = 1; i < FMath::Min(GetChildrenCount(), RequiredItems + 1); ++i)
    {
        GetChildAt(i)->SetVisibility(ESlateVisibility::Visible);
        UpdateDelegate.Broadcast(Cast<UCanvasPanel>(GetChildAt(i)), i - 1);
    }

    // add missing items
    for (int32 i = GetChildrenCount() - 1; i < RequiredItems; ++i)
        UpdateDelegate.Broadcast(Cast<UCanvasPanel>(AddItem()), i);

    // hide not needing items
    for (int32 i = GetChildrenCount() - 1; i > RequiredItems; --i)
        GetChildAt(GetChildrenCount() - 1)->SetVisibility(ESlateVisibility::Collapsed);

    RefreshGrid();
}

UCanvasPanel* UAGDynamicGrid::AddItem()
{
    UCanvasPanel* NewItem = Cast<UCanvasPanel>(UAGUIElementShared::DeepClone(TemplateItem, this));
    this->AddChild(NewItem); UAGUIElementShared::CopyTransform(TemplateItem->Slot, NewItem->Slot);
    NewItem->SetVisibility(ESlateVisibility::Visible);

    RefreshGrid();

    return NewItem;
}
