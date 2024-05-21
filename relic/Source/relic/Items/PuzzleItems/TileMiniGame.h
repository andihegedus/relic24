#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "InputAction.h"
#include "TileMiniGame.generated.h"

class USphereComponent;
class ATilePiece;
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

	void SelectTile();
	void PossessTile(const FInputActionValue& Value);
	
	void MoveSelectionUp(const FInputActionValue& Value);
	void MoveSelectionDown(const FInputActionValue& Value);
	void MoveSelectionLeft(const FInputActionValue& Value);
	void MoveSelectionRight(const FInputActionValue& Value);

	UFUNCTION()
	void OnPuzzleSolved();

	UFUNCTION()
	void GetOverlappingTiles(UPrimitiveComponent* Trigger);
	
	//UFUNCTION()
	//void UpdateSelection();

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

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ATilePiece* TilePiece;

	UPROPERTY(VisibleAnywhere)
	TArray<AActor*> Actors;
	
	UPROPERTY()
	ARelicHUD* HUD;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UInputMappingContext* PCMappingContext;

	UPROPERTY()
	TArray<AActor*> Pieces;

	UPROPERTY()
	bool bSolvedTilePuzzle;

	int32 SolutionCount;

	UPROPERTY()
	UMaterial* Highlight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ACameraActor* TileFacingCamera;

	int32 TileSelectNum;


protected:
	// FUNCTIONS
	// -----------------------------
	UFUNCTION()
	void CheckTilePlacement();
	

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
	TArray<UPrimitiveComponent*> Triggers;

	UPROPERTY(VisibleAnywhere, Category="Device | Components")
	TArray<UPrimitiveComponent*> OverlappingTiles;

	UPROPERTY(VisibleAnywhere, Category="Device | Components")
	TArray<UPrimitiveComponent*> AllTiles;

	UPROPERTY(VisibleAnywhere, Category="Device | Components")
	USphereComponent* TriggerOne;

	UPROPERTY(VisibleAnywhere, Category="Device | Components")
	USphereComponent* TriggerTwo;

	UPROPERTY(VisibleAnywhere, Category="Device | Components")
	USphereComponent* TriggerThree;

	UPROPERTY(VisibleAnywhere, Category="Device | Components")
	USphereComponent* TriggerFour;

	UPROPERTY(VisibleAnywhere, Category="Device | Components")
	USphereComponent* TriggerFive;

	UPROPERTY(VisibleAnywhere, Category="Device | Components")
	USphereComponent* TriggerSix;

	UPROPERTY(VisibleAnywhere, Category="Device | Components")
	USphereComponent* TriggerSeven;

	UPROPERTY(VisibleAnywhere, Category="Device | Components")
	USphereComponent* TriggerEight;

	UPROPERTY(VisibleAnywhere, Category="Device | Components")
	USphereComponent* TriggerNine;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Device | Components");
	UFloatingPawnMovement* TileMovement;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera");
	USpringArmComponent* SpringArmComp;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera");
	UCameraComponent* CameraComp;
};
