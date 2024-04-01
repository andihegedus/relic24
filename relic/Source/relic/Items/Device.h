#pragma once

#include "CoreMinimal.h"
#include "Components/TimelineComponent.h"
#include "GameFramework/Pawn.h"
#include "Device.generated.h"

class APCharacter;
class UTimelineComponent;
class UStaticMeshComponent;
class UCurveFloat;

UCLASS()
class ADevice : public AActor
{
	GENERATED_BODY()
	
public:
	// FUNCTIONS
	// -----------------------------
	ADevice();

	virtual void BeginPlay() override;

	UFUNCTION()
	void OnPuzzleSolved();

	UFUNCTION()
	void OnPuzzleAbandoned();
	

	// PROPERTIES & VARIABLES
	// -----------------------------

	FName DeviceTag;

	UPROPERTY(EditAnywhere)
	UCurveFloat* DeviceTimelineCurveFloat;

	UPROPERTY()
	APCharacter* PlayerCharacter;

	UPROPERTY()

protected:
	// FUNCTIONS
	// -----------------------------
	UFUNCTION()
	void UpdateTimelineComp(float Output);

	// PROPERTIES & VARIABLES
	// -----------------------------
	UPROPERTY(VisibleAnywhere, Category="Device | Components")
	UStaticMeshComponent* DeviceMeshComp;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UTimelineComponent* DeviceTimelineComp;

	FOnTimelineFloat UpdateFunctionFloatCeiling;
	
	
	
};
