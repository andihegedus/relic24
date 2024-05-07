#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "TilePiece.generated.h"

class USphereComponent;
class UStaticMeshComponent;

UCLASS()
class ATilePiece : public AActor
{
	GENERATED_BODY()
	
public:
	// FUNCTIONS
	// -----------------------------
	
	ATilePiece();
	

	// PROPERTIES & VARIABLES
	// -----------------------------

	FName TilePieceTag;
	
	UPROPERTY(VisibleAnywhere, Category="TilePiece | Components")
	UStaticMeshComponent* TilePieceComp;

	UPROPERTY(VisibleAnywhere, Category="TilePiece | Components")
	USphereComponent* SphereCollisionTop;

	UPROPERTY(VisibleAnywhere, Category="TilePiece | Components")
	USphereComponent* SphereCollisionBottom;

	UPROPERTY(VisibleAnywhere, Category="TilePiece | Components")
	USphereComponent* SphereCollisionLeft;

	UPROPERTY(VisibleAnywhere, Category="TilePiece | Components")
	USphereComponent* SphereCollisionRight;

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
	TArray<UPrimitiveComponent*> Pieces;
	
};
