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

	// To move (ACharacter)
	MoveAction = NewObject<UInputAction>(this);
	MoveAction->ValueType = EInputActionValueType::Axis3D;
	SetupKeyMap(PCMappingContext, MoveAction, EKeys::W, false, false, EInputAxisSwizzle::YXZ);
	SetupKeyMap(PCMappingContext, MoveAction, EKeys::S, true, false, EInputAxisSwizzle::YXZ);
	SetupKeyMap(PCMappingContext, MoveAction, EKeys::A, true, true, EInputAxisSwizzle::YXZ);
	SetupKeyMap(PCMappingContext, MoveAction, EKeys::D, false, true, EInputAxisSwizzle::YXZ);

	// To move tile up (ATilePiece)
	TileUpAction = NewObject<UInputAction>(this);
	TileUpAction->ValueType = EInputActionValueType::Axis3D;
	SetupKeyMap(PCMappingContext, TileUpAction, EKeys::W, false, false, EInputAxisSwizzle::YXZ);

	// To move tile down (ATilePiece)
	TileDownAction = NewObject<UInputAction>(this);
	TileDownAction->ValueType = EInputActionValueType::Axis3D;
	SetupKeyMap(PCMappingContext, MoveAction, EKeys::S, true, false, EInputAxisSwizzle::YXZ);

	// To move tile left (ATilePiece)
	TileLeftAction = NewObject<UInputAction>(this);
	TileLeftAction->ValueType = EInputActionValueType::Axis3D;
	SetupKeyMap(PCMappingContext, MoveAction, EKeys::A, true, true, EInputAxisSwizzle::YXZ);

	// To move tile right (ATilePiece)
	TileRightAction = NewObject<UInputAction>(this);
	TileRightAction->ValueType = EInputActionValueType::Axis3D;
	SetupKeyMap(PCMappingContext, MoveAction, EKeys::D, false, true, EInputAxisSwizzle::YXZ);

	// To move tile selection up (ATileGame)
	SelectUpAction = NewObject<UInputAction>(this);
	SelectUpAction->ValueType = EInputActionValueType::Axis3D;
	SetupKeyMap(PCMappingContext, SelectUpAction, EKeys::W, false, false, EInputAxisSwizzle::YXZ);

	// To move tile selection down (ATileGame)
	SelectDownAction = NewObject<UInputAction>(this);
	SelectDownAction->ValueType = EInputActionValueType::Axis3D;
	SetupKeyMap(PCMappingContext, SelectDownAction, EKeys::S, true, false, EInputAxisSwizzle::YXZ);
	
	// To move tile selection left (ATileGame)
	SelectLeftAction = NewObject<UInputAction>(this);
	SelectLeftAction->ValueType = EInputActionValueType::Axis3D;
	SetupKeyMap(PCMappingContext, SelectLeftAction, EKeys::A, true, true, EInputAxisSwizzle::YXZ);

	// To move tile selection right (ATileGame)
	SelectRightAction = NewObject<UInputAction>(this);
	SelectRightAction->ValueType = EInputActionValueType::Axis3D;
	SetupKeyMap(PCMappingContext, SelectRightAction, EKeys::D, false, true, EInputAxisSwizzle::YXZ);
	
	// To look (ACharacter)
	LookAction = NewObject<UInputAction>(this);
	LookAction->ValueType = EInputActionValueType::Axis3D;
	SetupKeyMap(PCMappingContext, LookAction, EKeys::MouseY, false, false, EInputAxisSwizzle::YXZ);
	SetupKeyMap(PCMappingContext, LookAction, EKeys::MouseX, false, true, EInputAxisSwizzle::YXZ);

	// To interact (ACharacter)
	InteractAction = NewObject<UInputAction>(this);
	InteractAction->ValueType = EInputActionValueType::Axis3D;
	SetupKeyMap(PCMappingContext, InteractAction, EKeys::E, false, false, EInputAxisSwizzle::YXZ);

	// To select a tile (ATileGame)
	TileSelectAction = NewObject<UInputAction>(this);
	TileSelectAction->ValueType = EInputActionValueType::Axis3D;
	SetupKeyMap(PCMappingContext, TileSelectAction, EKeys::Enter, false, false, EInputAxisSwizzle::YXZ);

	// To back out of current screen (ATilePiece)
	BackAction = NewObject<UInputAction>(this);
	BackAction->ValueType = EInputActionValueType::Axis3D;
	SetupKeyMap(PCMappingContext, BackAction, EKeys::Q, false, false, EInputAxisSwizzle::YXZ);

	// To activate device (ACharacter)
	DeviceAction = NewObject<UInputAction>(this);
	DeviceAction->ValueType = EInputActionValueType::Boolean;
	SetupKeyMap(PCMappingContext, DeviceAction, EKeys::E, false, false, EInputAxisSwizzle::YXZ);
	
	// To back out of puzzle screen, UnPossess puzzle
	EscapeAction = NewObject<UInputAction>(this);
	EscapeAction->ValueType = EInputActionValueType::Boolean;
	SetupKeyMap(PCMappingContext, EscapeAction, EKeys::Escape, false, false, EInputAxisSwizzle::YXZ);

	// To close the dialogue box
	CloseDialogueAction = NewObject<UInputAction>(this);
	CloseDialogueAction->ValueType = EInputActionValueType::Boolean;
	SetupKeyMap(PCMappingContext, CloseDialogueAction, EKeys::Enter, false, false, EInputAxisSwizzle::YXZ);

	// To dive 
	DiveAction = NewObject<UInputAction>(this);
	DiveAction->ValueType = EInputActionValueType::Axis3D;
	SetupKeyMap(PCMappingContext, DiveAction, EKeys::Q, false, false, EInputAxisSwizzle::YXZ);
}


