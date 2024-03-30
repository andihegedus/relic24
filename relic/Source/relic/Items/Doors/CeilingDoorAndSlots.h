#pragma once

#include "CoreMinimal.h"
#include "Components/TimelineComponent.h"
#include "CeilingDoorAndSlots.generated.h"

class UBoxComponent;
class UTimelineComponent;
class UActorComponent;
class UStaticMeshComponent;
class UCurveFloat;

UCLASS()
class RELIC_API ACeilingDoorAndSlots : public AActor
{
	GENERATED_BODY()
public:
	// FUNCTIONS
	// -----------------------------
	ACeilingDoorAndSlots();

	virtual void BeginPlay() override;
	

	// PROPERTIES & VARIABLES
	// -----------------------------
	FName DoorTag;
	
	UPROPERTY(EditAnywhere)
	UCurveFloat* DoorTimelineCurveFloat;

	

protected:
	// FUNCTIONS
	// -----------------------------
	UFUNCTION()
	void UpdateTimelineComp(float Output);

	UFUNCTION()
	void OnTriggerPuzzleSolution(UActorComponent* ActorComp, bool bIsTriggered);
	

	// PROPERTIES & VARIABLES
	// -----------------------------
	UPROPERTY(VisibleAnywhere, Category="Slot & Door | Components")
	UStaticMeshComponent* SlotMeshComp;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Slot & Door | Components")
	UStaticMeshComponent* DoorMeshComp;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Slot & Door | Components")
	UTimelineComponent* DoorTimelineComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Slot & Door | Components")
	UActorComponent* DoorSolutionTrigger;

	FOnTimelineFloat UpdateFunctionFloatCeiling;
	
};
