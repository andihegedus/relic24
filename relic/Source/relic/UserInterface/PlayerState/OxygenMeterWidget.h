#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/TimelineComponent.h"
#include "OxygenMeterWidget.generated.h"

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
	
	UPROPERTY()
	APCharacter* PlayerCharacter;

protected:
	// FUNCTIONS
	// -----------------------------

	
	// PROPERTIES & VARIABLES
	// -----------------------------
	
	// "BindWidget" makes it so the widget won't compile without the specified UProperty present
	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category="Interaction Widget | Interactable Info")
	UHorizontalBox* OxygenMeterBox;
	
	//UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category="Interaction Widget | Interactable Info")
	//UImage* OxygenMeterIcon;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category="Interaction Widget | Interactable Info")
	UTextBlock* OxygenPercentText;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category="Interaction Widget | Interactable Info")
	UTextBlock* WarningText;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category="Interaction Widget | Interactable Info")
	UProgressBar* OxygenProgressBar;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category="Interaction Widget | Interactable Info")
	float OxygenPercent;
};

