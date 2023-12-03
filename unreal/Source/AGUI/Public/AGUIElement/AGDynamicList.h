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
#include "Components/ScrollBox.h"
class UCanvasPanel;

#include "AGDynamicList.generated.h"

//! Reserved for "UAGDynamicList::UpdateDelegate"
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(
    FListView_UpdateDelegate,
    UCanvasPanel*, Item,
    int32, Index);

//# A list that you can add or remove its items runtime.
//! Component class; spawning expected.
UCLASS(NotBlueprintable, DisplayName="Dynamic List(AG)")
class UAGDynamicList final : public UScrollBox
{
    GENERATED_BODY()

protected:
    //# A template is using to add items to list.
    UPROPERTY(EditInstanceOnly, Category="Dynamic List")
    TObjectPtr<UCanvasPanel> TemplateItem;

    //# Use this to update items.
    UPROPERTY(BlueprintAssignable)
    FListView_UpdateDelegate UpdateDelegate;

public:
    //# Call on parent initialize.
    void Setup() const;

    //# Update the amount of items in grid and each one of them.
    UFUNCTION(BlueprintCallable)
    void Update(int32 RequiredItems);

private:
    UCanvasPanel* AddItem();
};
