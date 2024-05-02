#pragma once

#include "CoreMinimal.h"
#include "Components/TimelineComponent.h"
#include "TombWater.generated.h"

class APCharacter;
class UTimelineComponent;
class UBoxComponent;
class UStaticMeshComponent;
class UCurveFloat;

UCLASS()
class RELIC_API ATombWater : public AActor
{
	GENERATED_BODY()
	
public:
	// FUNCTIONS
	// -----------------------------
	ATombWater();

	virtual void BeginPlay() override;
	

	// PROPERTIES & VARIABLES
	// -----------------------------
	UPROPERTY(EditAnywhere)
	UCurveFloat* WaterTimelineCurveFloat;

	UPROPERTY(EditAnywhere)
	FVector InitialWaterLocation;

	UPROPERTY(EditAnywhere)
	FVector LevelOneWater;

	UPROPERTY(EditAnywhere)
	FVector LevelTwoWater;

	UPROPERTY(EditAnywhere)
	FVector LevelThreeWater;

	UPROPERTY(EditAnywhere)
	int32 WaterLevelID;

	

	UPROPERTY()
	APCharacter* PlayerCharacter;

protected:
	// FUNCTIONS
	// -----------------------------
	UFUNCTION()
	void UpdateTimelineComp(float Output);

	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* Actor,
		class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void RaiseWaterLevel();

	// PROPERTIES & VARIABLES
	// -----------------------------
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* WaterMeshComp;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UTimelineComponent* WaterTimelineComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UBoxComponent* WaterProxTrigger;

	FOnTimelineFloat UpdateFunctionFloat;

};
