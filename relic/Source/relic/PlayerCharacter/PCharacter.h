#pragma once

#include "CoreMinimal.h"
#include "Engine/Engine.h"
#include "InputActionValue.h"
#include "GameFramework/Character.h"
#include "relic/Items/Doors/TombCeilingDoor.h"
#include "PCharacter.generated.h"

class ATombCeilingDoor;
class ARelicHUD;
class UInputMappingContext;
class UInputAction;
class USpringArmComponent;
class UCameraComponent;

DECLARE_MULTICAST_DELEGATE(FOnMedallionPlaced);
DECLARE_MULTICAST_DELEGATE(FOnTilePuzzleSolved);
DECLARE_MULTICAST_DELEGATE(FOnDeviceActivated);
DECLARE_MULTICAST_DELEGATE(FOnDeviceAbandoned);

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

	FName PlayerTag;
	
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

	bool bIsDiving;
	
	int32 DiveTimerLoopCount;

	int32 DeviceTimerLoopCount;

	// Puzzle solution delegates, these delegate events will trigger door(s) opening after puzzles are solved
	FOnMedallionPlaced OnMedallionPlaced;

	// Might need to move this to its own script depending on tile puzzle implementation
	FOnTilePuzzleSolved OnTilePuzzleSolved;

	FOnDeviceActivated OnDeviceActivated;

	FOnDeviceAbandoned OnDeviceAbandoned;
	
	UPROPERTY()
	ATombCeilingDoor* TombCeilingDoor;

protected:
	// FUNCTIONS
	// -----------------------------

	// Move
	void Idle();
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void Dive(const FInputActionValue& Value);
	void DiveTimer();

	// Interact
	void CheckForInteractable();
	void FoundInteractable();
	void NoInteractableFound();
	void StartInteract();
	void CompleteInteract();
	void DeviceTimer();
	void DeviceAbandoned();

	// End State
	void Death();

	
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

	UPROPERTY(EditAnywhere)
	float DelayAfterSolution;
	
	FTimerHandle SolutionTimerHandle;
	
	FTimerHandle OxygenTimerHandle;

};
