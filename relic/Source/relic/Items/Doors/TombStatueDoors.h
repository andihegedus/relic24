#pragma once

#include "CoreMinimal.h"
#include "Components/TimelineComponent.h"
#include "TombStatueDoors.generated.h"

class APCharacter;
class UBoxComponent;
class UTimelineComponent;
class UActorComponent;
class UStaticMeshComponent;
class UCurveFloat;

UCLASS()
class ATombStatueDoors : public AActor
{
	GENERATED_BODY()
public:
	// FUNCTIONS
	// -----------------------------
	ATombStatueDoors();

	virtual void BeginPlay() override;

	UFUNCTION()
	void OnPuzzleSolved();
	

	// PROPERTIES & VARIABLES
	// -----------------------------
	FName StatueTag;
	
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
	UStaticMeshComponent* StatueMeshComp;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UTimelineComponent* DoorTimelineComp;

	FOnTimelineFloat UpdateFunctionFloatCeiling;
	
};
