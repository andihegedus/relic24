#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Slot.generated.h"

UCLASS()
class RELIC_API ASlot : public AActor
{
	GENERATED_BODY()
	
public:
	// FUNCTIONS
	// -----------------------------
	
	ASlot();

	// PROPERTIES & VARIABLES
	// -----------------------------

	FName SlotTag;
	
	UPROPERTY(VisibleAnywhere, Category="Slot | Components")
	UStaticMeshComponent* SlotMeshComp;


protected:
	// FUNCTIONS
	// -----------------------------

	virtual void BeginPlay() override;
	
};
