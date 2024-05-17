#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "InputAction.h"
#include "TilePiece.generated.h"

class ATileMiniGame;
class USphereComponent;
class UStaticMeshComponent;
class USphereComponent;
class ARelicHUD;
class UFloatingPawnMovement;
class APCharacter;
class APController;
class UStaticMeshComponent;
class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
class UMaterial;

UCLASS()
class ATilePiece : public APawn
{
	GENERATED_BODY()
	
public:
	// FUNCTIONS
	// -----------------------------
	
	ATilePiece();
	
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	void MoveTile(const FInputActionValue& Value);
	
	UFUNCTION()
	void OnBecomePossessed();

	UFUNCTION()
	void OnBecomeUnPossessed();

	UFUNCTION()
	void HighlightTile();

	UFUNCTION()
	void HideHighlight();
	

	// PROPERTIES & VARIABLES
	// -----------------------------

	FName TilePieceTag;
	
	UPROPERTY(VisibleAnywhere, Category="TilePiece | Components")
	UStaticMeshComponent* TilePieceComp;

	UPROPERTY(VisibleAnywhere, Category="TilePiece | Components")
	USphereComponent* SphereCollision;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	APCharacter* PlayerCharacter;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	APController* PlayerController;

	UPROPERTY()
	ARelicHUD* HUD;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UInputMappingContext* PCMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ATileMiniGame* TileMiniGame;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UMaterial* HighlightMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UMaterial* TransparentMaterial;
	
	bool bAllNeighborsFound;

	int32 TileID;
	

protected:
	// FUNCTIONS
	// -----------------------------

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

	
	// PROPERTIES & VARIABLES
	// -----------------------------
	
	UPROPERTY()
	TArray<UPrimitiveComponent*> Neighbors;

	UPROPERTY()
	TArray<AActor*> Actors;

	UPROPERTY()
	UPrimitiveComponent* Neighbor;
	
};
