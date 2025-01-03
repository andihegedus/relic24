﻿#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InputMappingContext.h"
#include "PController.generated.h"

UCLASS()
class RELIC_API APController : public APlayerController
{
	GENERATED_BODY()
	
public:
	// FUNCTIONS
	// -----------------------------

	static void SetupKeyMap(UInputMappingContext* InputMappingContext, UInputAction* InputAction,
		FKey Key, bool bNegate, bool bSwizzle, EInputAxisSwizzle SwizzleOrder);

	virtual void SetupInputComponent() override;


	// PROPERTIES & VARIABLES
	// -----------------------------

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UInputMappingContext* PCMappingContext;

	UPROPERTY()
	class UInputAction* MoveAction;

	UPROPERTY()
	class UInputAction* SelectUpAction;

	UPROPERTY()
	class UInputAction* SelectDownAction;

	UPROPERTY()
	class UInputAction* SelectLeftAction;

	UPROPERTY()
	class UInputAction* SelectRightAction;

	UPROPERTY()
	class UInputAction* LookAction;

	UPROPERTY()
	class UInputAction* RunAction;

	UPROPERTY()
	class UInputAction* DiveAction;

	UPROPERTY()
	class UInputAction* InteractAction;

	UPROPERTY()
	class UInputAction* TileSelectAction;

	UPROPERTY()
	class UInputAction* BackAction;

	UPROPERTY()
	class UInputAction* TileMoveAction;

	UPROPERTY()
	class UInputAction* TileUpAction;

	UPROPERTY()
	class UInputAction* TileDownAction;

	UPROPERTY()
	class UInputAction* TileLeftAction;

	UPROPERTY()
	class UInputAction* TileRightAction;

	UPROPERTY()
	class UInputAction* AimAction;

	UPROPERTY()
	class UInputAction* ToggleMenuAction;

	UPROPERTY()
	class UInputAction* ToggleDebugMenuAction;

	UPROPERTY()
	class UInputAction* DeviceAction;

	UPROPERTY()
	class UInputAction* EscapeAction;

	UPROPERTY()
	class UInputAction* CloseDialogueAction;
	
};
