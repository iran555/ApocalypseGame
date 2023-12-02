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
#include "Components/UniformGridPanel.h"
class UCanvasPanel;

#include "AGDynamicGrid.generated.h"

//! Reserved for "UAGDynamicGrid::UpdateDelegate"
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(
    FGridView_UpdateDelegate,
    UCanvasPanel*, Item,
    int32, Index);

//# A grid that you can add or remove its items runtime.
//! Component class; spawning expected.
UCLASS(NotBlueprintable, DisplayName="Dynamic Grid(AG)")
class UAGDynamicGrid : public UUniformGridPanel
{
    GENERATED_BODY()

protected:
    //# A template is using to add items to list.
    UPROPERTY(EditInstanceOnly, Category="Dynamic Grid")
    TObjectPtr<UCanvasPanel> TemplateItem = nullptr;

    //# Use this to update items.
    UPROPERTY(BlueprintAssignable)
    FGridView_UpdateDelegate UpdateDelegate = {};

    //# Count of rows on this grid.
    //! Call RefreshGrid on change.
    UPROPERTY(EditInstanceOnly, Category="Dynamic Grid")
    uint8 RowCount = 3;

public:
    //# Call on parent initialize.
    UFUNCTION(BlueprintCallable)
    void Setup() const;

    //# Update the grid row and column.
    UFUNCTION(BlueprintCallable)
    void RefreshGrid() const;

    //# Update the amount of items in grid and each one of them.
    UFUNCTION(BlueprintCallable)
    void Update(int32 RequiredItems);

private:
    UCanvasPanel* AddItem();
};
