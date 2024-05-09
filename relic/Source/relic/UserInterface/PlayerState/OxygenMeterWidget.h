#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/TimelineComponent.h"
#include "OxygenMeterWidget.generated.h"

class UMaterialInstance;
class UMaterialInstanceDynamic;
class UImage;
class APCharacter;
class UProgressBar;
class UTextBlock;
class UHorizontalBox;

UCLASS()
class UOxygenMeterWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	// FUNCTIONS
	// -----------------------------
	
	void UpdateWidget(FTimerHandle TimerHandle, float UpdatedPercent);

	virtual void NativeOnInitialized() override;

	virtual void NativeConstruct() override;

	void SetRoundPBPercent(float Percent);

	

	// PROPERTIES & VARIABLES
	// -----------------------------
	
	UPROPERTY()
	APCharacter* PlayerCharacter;

	UPROPERTY(EditAnywhere, Category="Oxygen Meter Widget")
	UMaterialInstanceDynamic* RoundBarMatInstDynamic;

	UPROPERTY(EditAnywhere, Category="Oxygen Meter Widget")
	UMaterialInstance* RoundBarMaterial;


protected:
	// FUNCTIONS
	// -----------------------------

	
	// PROPERTIES & VARIABLES
	// -----------------------------
	
	// "BindWidget" makes it so the widget won't compile without the specified UProperty present
	//UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category="Interaction Widget | Interactable Info")
	//UHorizontalBox* OxygenMeterBox;
	
	//UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category="Interaction Widget | Interactable Info")
	//UImage* OxygenMeterIcon;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category="Oxygen Meter Widget")
	UTextBlock* OxygenPercentText;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category="Oxygen Meter Widget")
	UTextBlock* WarningText;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category="Oxygen Meter Widget")
	UProgressBar* OxygenProgressBar;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget), Category="Oxygen Meter Widget")
	UImage* RoundBarImage;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category="Oxygen Meter Widget")
	float OxygenPercent;

	
};

