#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Pickup.generated.h"

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

protected:
	// FUNCTIONS
	// -----------------------------

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

	void Interact(APCharacter* PlayerCharacter);

	void TakePickup(const APCharacter* Taker);

	// PROPERTIES & VARIABLES
	// -----------------------------
	
	
};
