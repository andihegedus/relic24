#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Pickup.generated.h"

UCLASS()
class APickup : public AActor
{
	GENERATED_BODY()
	
public:
	// FUNCTIONS
	// -----------------------------
	
	APickup();

protected:
	// FUNCTIONS
	// -----------------------------

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;
	
};
