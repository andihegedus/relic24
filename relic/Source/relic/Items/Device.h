#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Device.generated.h"

UCLASS()
class ADevice : public AActor
{
	GENERATED_BODY()
	
public:
	// FUNCTIONS
	// -----------------------------
	
	ADevice();
	

	// PROPERTIES & VARIABLES
	// -----------------------------

	FName DeviceTag;
	
	UPROPERTY(VisibleAnywhere, Category="Pickup | Components")
	UStaticMeshComponent* DeviceMeshComp;

protected:
	// FUNCTIONS
	// -----------------------------

	virtual void BeginPlay() override;
	
	
	
};
