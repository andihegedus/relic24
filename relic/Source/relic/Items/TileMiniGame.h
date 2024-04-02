﻿#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "InputAction.h"
#include "TileMiniGame.generated.h"

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

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	void MoveTiles(const FInputActionValue& Value);
	
	UFUNCTION()
	void OnPuzzleSolved();

	UFUNCTION()
	void OnPuzzleAbandoned();

	UFUNCTION()
	void OnBecomePossessed();

	// PROPERTIES & VARIABLES
	// -----------------------------

	FName MiniGameTag;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	APCharacter* PlayerCharacter;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	APController* PlayerController;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UInputMappingContext* PCMappingContext;

protected:
	// FUNCTIONS
	// -----------------------------

	

	// PROPERTIES & VARIABLES
	// -----------------------------
	UPROPERTY(VisibleAnywhere, Category="Device | Components")
	UStaticMeshComponent* BaseMeshComp;

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
