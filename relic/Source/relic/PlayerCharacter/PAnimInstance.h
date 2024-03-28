#pragma once

#include "Animation/AnimInstance.h"
#include "PAnimInstance.generated.h"

class APCharacter;
class UCharacterMovementComponent;

UCLASS()
class UPAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	// FUNCTIONS
	// -----------------------------
	
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
	

	// PROPERTIES & VARIABLES
	// -----------------------------

	UPROPERTY(BlueprintReadOnly)
	class APCharacter* PlayerCharacter;

	UPROPERTY(BlueprintReadOnly, Category = Movement)
	class UCharacterMovementComponent* PCMovement;

	UPROPERTY(BlueprintReadWrite, Category = Movement)
	float Speed;

	UPROPERTY(BlueprintReadWrite, Category = Movement)
	float MaxSpeed;

	UPROPERTY(BlueprintReadWrite)
	bool bIsInteracting;
	
};
