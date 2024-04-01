#pragma once

#include "CoreMinimal.h"
#include "Components/TimelineComponent.h"
#include "TombCeilingDoor.generated.h"

class APCharacter;
class UBoxComponent;
class UTimelineComponent;
class UStaticMeshComponent;
class UCurveFloat;

UCLASS()
class RELIC_API ATombCeilingDoor : public AActor
{
	GENERATED_BODY()
	
public:
	// FUNCTIONS
	// -----------------------------
	ATombCeilingDoor();

	virtual void BeginPlay() override;

	UFUNCTION()
	void OnPuzzleSolved();
	

	// PROPERTIES & VARIABLES
	// -----------------------------
	FName DoorTag;
	
	UPROPERTY(EditAnywhere)
	UCurveFloat* DoorTimelineCurveFloat;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UBoxComponent* DoorSolutionTrigger;

	UPROPERTY()
	APCharacter* PlayerCharacter;

protected:
	// FUNCTIONS
	// -----------------------------
	UFUNCTION()
	void UpdateTimelineComp(float Output);

	// PROPERTIES & VARIABLES
	// -----------------------------
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Door;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UTimelineComponent* DoorTimelineComp;

	FOnTimelineFloat UpdateFunctionFloatCeiling;

	
};
