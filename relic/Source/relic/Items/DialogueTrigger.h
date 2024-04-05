#pragma once

#include "CoreMinimal.h"
#include "DialogueTrigger.generated.h"

class APCharacter;
class ARelicHUD;
class UBoxComponent;
class UStaticMeshComponent;

UCLASS()
class RELIC_API ADialogueTrigger : public AActor
{
	GENERATED_BODY()
	
public:
	// FUNCTIONS
	// -----------------------------
	ADialogueTrigger();

	virtual void BeginPlay() override;

	void CloseAndDestroy();

	// PROPERTIES & VARIABLES
	// -----------------------------

	UPROPERTY()
	ARelicHUD* HUD;

	UPROPERTY()
	APCharacter* PlayerCharacter;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName TriggerTag;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 LocationID;

protected:
	// FUNCTIONS
	// -----------------------------

	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* Actor,
		class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	

	// PROPERTIES & VARIABLES
	// -----------------------------
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UBoxComponent* DialogueProxTrigger;
	
};
