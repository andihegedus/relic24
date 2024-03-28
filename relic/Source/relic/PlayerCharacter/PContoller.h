#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InputMappingContext.h"
#include "PContoller.generated.h"

UCLASS()
class APContoller : public APlayerController
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

	UPROPERTY()
	class UInputMappingContext* PCMappingContext;

	UPROPERTY()
	class UInputAction* MoveAction;

	UPROPERTY()
	class UInputAction* LookAction;

	UPROPERTY()
	class UInputAction* RunAction;

	UPROPERTY()
	class UInputAction* InteractAction;

	UPROPERTY()
	class UInputAction* AimAction;

	UPROPERTY()
	class UInputAction* ToggleMenuAction;

	UPROPERTY()
	class UInputAction* ToggleDebugMenuAction;
	
};
