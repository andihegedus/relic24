#pragma once

#include "CoreMinimal.h"
#include "Components/TimelineComponent.h"
#include "TombEntranceDoor.generated.h"

class UTimelineComponent;
class UBoxComponent;
class UStaticMeshComponent;
class UCurveFloat;

UCLASS()
class RELIC_API ATombEntranceDoor : public AActor
{
	 GENERATED_BODY()
	
public:
	// FUNCTIONS
	// -----------------------------
	ATombEntranceDoor();

	virtual void BeginPlay() override;
	

	// PROPERTIES & VARIABLES
	// -----------------------------
	UPROPERTY(EditAnywhere)
	UCurveFloat* DoorTimelineCurveFloat;

protected:
	// FUNCTIONS
	// -----------------------------
	UFUNCTION()
	void UpdateTimelineComp(float Output);

	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* Actor,
		class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* Actor,
		class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	

	// PROPERTIES & VARIABLES
	// -----------------------------
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Door;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UTimelineComponent* DoorTimelineComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UBoxComponent* DoorProxTrigger;

	FOnTimelineFloat UpdateFunctionFloat;
};
