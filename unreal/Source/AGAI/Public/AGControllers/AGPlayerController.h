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
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

#include "AGPlayerController.generated.h"

//! Reserved for "AAGPlayerController::InputMode"
UENUM(BlueprintType)
enum class EAGPlayerController_InputMode : uint8
{
	OnFoot
};

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

public:
	//# input mode is define what and how input handled.
	//! On change call "UpdateInputMode".
	UPROPERTY(VisibleInstanceOnly, Category="Input")
	EAGPlayerController_InputMode InputMode = EAGPlayerController_InputMode::OnFoot;

	void UpdateInputMode();

protected:
	//# InputMappingContext asset created for this class.
	UPROPERTY(EditDefaultsOnly, Category="Input")
	TSoftObjectPtr<UInputMappingContext> PlayerControllerInputMapping = nullptr;

	//# Direct move input.
	//* WASD in most games.
	//! Holds index 0 at MappingContext. Carry 2D data.
	UPROPERTY(EditDefaultsOnly, Category="Input|Actions")
	TSoftObjectPtr<UInputAction> Move_InputAction;
	void Move_InputHandel(const FInputActionValue& RawInput);

	//# Change the angel of look with this.
	//* mouse in most games.
	//! Holds index 1 at MappingContext. Carry 2D data.
	UPROPERTY(EditDefaultsOnly, Category="Input|Actions")
	TSoftObjectPtr<UInputAction> Look_InputAction;
	void Look_InputHandel(const FInputActionValue& RawInput);

#pragma endregion Input
};
