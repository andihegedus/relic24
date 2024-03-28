#pragma once

#include "CoreMinimal.h"
#include "Engine/Engine.h"
#include "GameFramework/Character.h"
#include "PCharacter.generated.h"

class ARelicHUD;
class UInputMappingContext;
class UInputAction;
class USpringArmComponent;
class UCameraComponent;

UCLASS()
class RELIC_API APCharacter: public ACharacter
{
	GENERATED_BODY()
	
public:
	// FUNCTIONS
	// -----------------------------

	APCharacter();

	virtual void Tick(float DeltaSeconds) override;

	virtual void BeginPlay() override;

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

protected:
	// PROPERTIES & VARIABLES
	// -----------------------------

	//UPROPERTY()
	//ARelicHUD* HUD;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera");
	USpringArmComponent* SpringArmComp;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera");
	UCameraComponent* CameraComp;
};
