#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "TilePiece.generated.h"

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

UCLASS()
class ATilePiece : public APawn
{
	GENERATED_BODY()
	
public:
	// FUNCTIONS
	// -----------------------------
	
	ATilePiece();

	UFUNCTION()
	void OnBecomePossessed();

	UFUNCTION()
	void OnBecomeUnPossessed();
	

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
	ATilePiece* TilePiece;

	/*UPROPERTY(VisibleAnywhere, Category="TilePiece | Components")
	USphereComponent* SphereCollisionTop;

	UPROPERTY(VisibleAnywhere, Category="TilePiece | Components")
	USphereComponent* SphereCollisionBottom;

	UPROPERTY(VisibleAnywhere, Category="TilePiece | Components")
	USphereComponent* SphereCollisionLeft;

	UPROPERTY(VisibleAnywhere, Category="TilePiece | Components")
	USphereComponent* SphereCollisionRight;*/

	bool bAllNeighborsFound;

protected:
	// FUNCTIONS
	// -----------------------------

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

	UFUNCTION()
	void FindAdjacentTile();

	//UFUNCTION()
	//void AllNeighborsFound();
	

	// PROPERTIES & VARIABLES
	// -----------------------------
	
	UPROPERTY()
	TArray<UPrimitiveComponent*> Neighbors;

	UPROPERTY()
	TArray<AActor*> Actors;

	UPROPERTY()
	UPrimitiveComponent* Neighbor;
	
};
