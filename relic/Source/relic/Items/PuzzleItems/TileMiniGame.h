#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "InputAction.h"
#include "TileMiniGame.generated.h"

class UBoxComponent;
class ARelicHUD;
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
class ATileMiniGame : public APawn
{
	GENERATED_BODY()
public:
	// FUNCTIONS
	// -----------------------------
	ATileMiniGame();

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	void SelectTile(const FInputActionValue& Value);
	void DragTiles(const FInputActionValue& Value);
	void DropTiles(const FInputActionValue& Value);
	
	UFUNCTION()
	void OnPuzzleSolved();

	UFUNCTION()
	void OnPuzzleAbandoned();

	UFUNCTION()
	void OnBecomePossessed();

	UFUNCTION()
	void OnBecomeUnPossessed();

	// PROPERTIES & VARIABLES
	// -----------------------------

	FName MiniGameTag;

	bool bIsGaming;

	bool bIsSelected;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	APCharacter* PlayerCharacter;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	APController* PlayerController;

	UPROPERTY()
	ARelicHUD* HUD;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UInputMappingContext* PCMappingContext;

	UPROPERTY()
	bool bSolvedTilePuzzle;

protected:
	// FUNCTIONS
	// -----------------------------

	

	// PROPERTIES & VARIABLES
	// -----------------------------
	UPROPERTY()
	TArray<UStaticMeshComponent*> TileInFocus;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Device | Components")
	UBoxComponent* BoxCollision;

	UPROPERTY(VisibleAnywhere, Category="Device | Components")
	UStaticMeshComponent* TileHolder;

	UPROPERTY(VisibleAnywhere, Category="Device | Components")
	TArray<UStaticMeshComponent*> Tiles;

	UPROPERTY(VisibleAnywhere, Category="Device | Components")
	UStaticMeshComponent* TileOne;

	UPROPERTY(VisibleAnywhere, Category="Device | Components")
	UStaticMeshComponent* TileTwo;

	UPROPERTY(VisibleAnywhere, Category="Device | Components")
	UStaticMeshComponent* TileThree;

	UPROPERTY(VisibleAnywhere, Category="Device | Components")
	UStaticMeshComponent* TileFour;

	UPROPERTY(VisibleAnywhere, Category="Device | Components")
	UStaticMeshComponent* TileFive;

	UPROPERTY(VisibleAnywhere, Category="Device | Components")
	UStaticMeshComponent* TileSix;

	UPROPERTY(VisibleAnywhere, Category="Device | Components")
	UStaticMeshComponent* TileSeven;

	UPROPERTY(VisibleAnywhere, Category="Device | Components")
	UStaticMeshComponent* TileEight;

	UPROPERTY(VisibleAnywhere, Category="Device | Components")
	UStaticMeshComponent* TileNine;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Device | Components");
	UFloatingPawnMovement* TileMovement;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera");
	USpringArmComponent* SpringArmComp;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera");
	UCameraComponent* CameraComp;
	
	
	
	
};
