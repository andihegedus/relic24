#pragma once

#include "CoreMinimal.h"
#include "Engine/Engine.h"
#include "InputActionValue.h"
#include "GameFramework/Character.h"
#include "PCharacter.generated.h"

class ARelicHUD;
class UInputMappingContext;
class UInputAction;
class USpringArmComponent;
class UCameraComponent;

USTRUCT()
struct FInteractionInfo
{
	GENERATED_BODY()

	// FUNCTIONS
	// -----------------------------

	FInteractionInfo() : InteractableItem(nullptr),InteractableComponent(nullptr), CheckLastInteractionTime(0.0f)
	{
	};

	// PROPERTIES & VARIABLES
	// -----------------------------

	UPROPERTY()
	AActor* InteractableItem;

	UPROPERTY()
	UPrimitiveComponent* InteractableComponent;

	// If over the elapsed in-game time, shoot another line trace for interactable objects
	// Not necessary to shoot trace every single frame
	UPROPERTY()
	float CheckLastInteractionTime;
};

UCLASS()
class RELIC_API APCharacter: public ACharacter
{
	GENERATED_BODY()
	
public:
	// FUNCTIONS
	// -----------------------------

	APCharacter();

	virtual void Tick(float DeltaSeconds) override;

	virtual void BeginPlay() override;

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;


	// PROPERTIES & VARIABLES
	// -----------------------------
	
	UPROPERTY(VisibleAnywhere, Category="Character | Inventory")
	FName CurrentTag;

	UPROPERTY(VisibleAnywhere, Category="Character | Inventory")
	TArray<FName> TagInFocus;

	UPROPERTY(VisibleAnywhere, Category="Character | Inventory")
	int32 InventoryQuantity;

	UPROPERTY(VisibleAnywhere, Category="Character | Inventory")
	TArray<AActor*> ItemsToDestroy;

	UPROPERTY(VisibleAnywhere, Category="Puzzle | Solutions")
	TArray<AActor*> ItemsToAppear;

	bool bIsInteracting;

	

protected:
	// FUNCTIONS
	// -----------------------------

	// Move
	void Idle();
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);

	// Interact
	void CheckForInteractable();
	void FoundInteractable();
	void NoInteractableFound();
	void StartInteract();
	void CompleteInteract();

	
	// PROPERTIES & VARIABLES
	// -----------------------------

	UPROPERTY()
	ARelicHUD* HUD;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera");
	USpringArmComponent* SpringArmComp;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera");
	UCameraComponent* CameraComp;

	FVector LineTraceStart;

	float MaxInteractTime;
	FInteractionInfo InteractionInfo;
	FTimerHandle InteractionTimerHandle;
	float CheckInteractionDistance;
	float CheckInteractionFrequency;
	
};
