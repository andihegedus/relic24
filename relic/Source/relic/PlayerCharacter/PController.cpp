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
}
