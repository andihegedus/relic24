#include "PController.h"
#include "PCharacter.h"

void APController::SetupKeyMap(UInputMappingContext* InputMappingContext, UInputAction* InputAction, FKey Key,
	bool bNegate, bool bSwizzle, EInputAxisSwizzle SwizzleOrder)
{
	FEnhancedActionKeyMapping& KeyMapping = InputMappingContext->MapKey(InputAction, Key);
	UObject* MapObject = InputMappingContext->GetOuter();

	if (bNegate)
	{
		UInputModifierNegate* Negate = NewObject<UInputModifierNegate>(MapObject);
		KeyMapping.Modifiers.Add(Negate);
	}

	if (bSwizzle)
	{
		UInputModifierSwizzleAxis* Swizzle = NewObject<UInputModifierSwizzleAxis>(MapObject);
		Swizzle->Order = SwizzleOrder;
		KeyMapping.Modifiers.Add(Swizzle);
	}
}

void APController::SetupInputComponent()
{
	Super::SetupInputComponent();

	PCMappingContext = NewObject<UInputMappingContext>(this);

	// To move
	MoveAction = NewObject<UInputAction>(this);
	MoveAction->ValueType = EInputActionValueType::Axis3D;
	SetupKeyMap(PCMappingContext, MoveAction, EKeys::W, false, false, EInputAxisSwizzle::YXZ);
	SetupKeyMap(PCMappingContext, MoveAction, EKeys::S, true, false, EInputAxisSwizzle::YXZ);
	SetupKeyMap(PCMappingContext, MoveAction, EKeys::A, true, true, EInputAxisSwizzle::YXZ);
	SetupKeyMap(PCMappingContext, MoveAction, EKeys::D, false, true, EInputAxisSwizzle::YXZ);

	// To look 
	LookAction = NewObject<UInputAction>(this);
	LookAction->ValueType = EInputActionValueType::Axis3D;
	SetupKeyMap(PCMappingContext, LookAction, EKeys::MouseY, false, false, EInputAxisSwizzle::YXZ);
	SetupKeyMap(PCMappingContext, LookAction, EKeys::MouseX, false, true, EInputAxisSwizzle::YXZ);

	// To interact
	InteractAction = NewObject<UInputAction>(this);
	InteractAction->ValueType = EInputActionValueType::Axis3D;
	SetupKeyMap(PCMappingContext, InteractAction, EKeys::E, false, false, EInputAxisSwizzle::YXZ);

	// To activate device
	DeviceAction = NewObject<UInputAction>(this);
	DeviceAction->ValueType = EInputActionValueType::Boolean;
	SetupKeyMap(PCMappingContext, DeviceAction, EKeys::E, false, false, EInputAxisSwizzle::YXZ);

	// To play Tile Mini Game
	TileGameAction = NewObject<UInputAction>(this);
	TileGameAction->ValueType = EInputActionValueType::Axis2D;
	SetupKeyMap(PCMappingContext, TileGameAction, EKeys::LeftMouseButton, true, true, EInputAxisSwizzle::YXZ);

	// To Select a Tile in Mini Game
	SelectTileAction = NewObject<UInputAction>(this);
	SelectTileAction->ValueType = EInputActionValueType::Axis3D;
	SetupKeyMap(PCMappingContext, SelectTileAction, EKeys::MouseY, false, false, EInputAxisSwizzle::YXZ);
	SetupKeyMap(PCMappingContext, SelectTileAction, EKeys::MouseX, false, true, EInputAxisSwizzle::YXZ);

	// To back out of screen
	EscapeAction = NewObject<UInputAction>(this);
	EscapeAction->ValueType = EInputActionValueType::Boolean;
	SetupKeyMap(PCMappingContext, EscapeAction, EKeys::Escape, false, false, EInputAxisSwizzle::YXZ);

	// To dive 
	DiveAction = NewObject<UInputAction>(this);
	DiveAction->ValueType = EInputActionValueType::Axis3D;
	SetupKeyMap(PCMappingContext, DiveAction, EKeys::Q, false, false, EInputAxisSwizzle::YXZ);
}


