#pragma once

#include "CoreMinimal.h"
#include "Components/TimelineComponent.h"
#include "TombCeilingDoor.generated.h"

class APCharacter;
class UBoxComponent;
class UTimelineComponent;
class UActorComponent;
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
	

	// PROPERTIES & VARIABLES
	// -----------------------------
	FName DoorTag;
	
	UPROPERTY(EditAnywhere)
	UCurveFloat* DoorTimelineCurveFloat;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UBoxComponent* DoorSolutionTrigger;

	UPROPERTY(BlueprintReadWRite, EditAnywhere)
	TSubclassOf<APCharacter> PlayerCharacter;

	UPROPERTY()
	APCharacter* Player;

protected:
	// FUNCTIONS
	// -----------------------------
	UFUNCTION()
	void UpdateTimelineComp(float Output);

	/*UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* Actor,
		class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);*/
	
	UFUNCTION()
	void OnPuzzleSolved();

	// PROPERTIES & VARIABLES
	// -----------------------------
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Door;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UTimelineComponent* DoorTimelineComp;

	FOnTimelineFloat UpdateFunctionFloatCeiling;

	
};
