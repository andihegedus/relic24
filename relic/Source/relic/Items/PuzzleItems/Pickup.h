#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Pickup.generated.h"

class UBoxComponent;
class UStaticMeshComponent;
class APCharacter;

UCLASS()
class RELIC_API APickup : public AActor
{
	GENERATED_BODY()
	
public:
	// FUNCTIONS
	// -----------------------------
	
	APickup();
	

	// PROPERTIES & VARIABLES
	// -----------------------------

	FName PickupTag;
	
	UPROPERTY(VisibleAnywhere, Category="Pickup | Components")
	UStaticMeshComponent* PickupMeshComp;

	UPROPERTY(VisibleAnywhere, Category="Pickup | Components")
	UBoxComponent* BoxCollision;

protected:
	// FUNCTIONS
	// -----------------------------

	virtual void BeginPlay() override;
	
	
	
};
