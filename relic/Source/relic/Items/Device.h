#pragma once

#include "CoreMinimal.h"
#include "Components/TimelineComponent.h"
#include "GameFramework/Pawn.h"
#include "InputAction.h"
#include "Device.generated.h"

class UFloatingPawnMovement;
class APCharacter;
class APController;
class UTimelineComponent;
class UStaticMeshComponent;
class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UCurveFloat;
class UInputAction;


UCLASS()
class ADevice : public APawn
{
	GENERATED_BODY()
	
public:
	// FUNCTIONS
	// -----------------------------
	ADevice();

	virtual void BeginPlay() override;

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	void Move(const FInputActionValue& Value);
	
	UFUNCTION()
	void OnPuzzleSolved();

	UFUNCTION()
	void OnPuzzleAbandoned();

	UFUNCTION()
	void OnBecomePossessed();

	
	

	// PROPERTIES & VARIABLES
	// -----------------------------

	FName DeviceTag;

	UPROPERTY(EditAnywhere)
	UCurveFloat* DeviceTimelineCurveFloat;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	APCharacter* PlayerCharacter;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	APController* PlayerController;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UInputMappingContext* PCMappingContext;

	UPROPERTY()
	class UInputAction* MoveAction;

protected:
	// FUNCTIONS
	// -----------------------------
	UFUNCTION()
	void UpdateTimelineComp(float Output);

	// PROPERTIES & VARIABLES
	// -----------------------------
	UPROPERTY(VisibleAnywhere, Category="Device | Components")
	UStaticMeshComponent* DeviceMeshComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Device | Components");
	UFloatingPawnMovement* DeviceMovement;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera");
	USpringArmComponent* SpringArmComp;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera");
	UCameraComponent* CameraComp;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UTimelineComponent* DeviceTimelineComp;

	FOnTimelineFloat UpdateFunctionFloatCeiling;
	
	
	
};
