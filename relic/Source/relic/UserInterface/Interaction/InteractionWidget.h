#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "InteractionWidget.generated.h"

class APCharacter;
class APickup;
class UProgressBar;
class UTextBlock;
class UHorizontalBox;

UCLASS()
class RELIC_API UInteractionWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	// FUNCTIONS
	// -----------------------------
	
	void UpdateWidget(const TArray<FName> Tags);
	

	// PROPERTIES & VARIABLES
	// -----------------------------

	UPROPERTY()
	APickup* PickupComponent;

	UPROPERTY()
	APCharacter* PlayerCharacter;


protected:
	// FUNCTIONS
	// -----------------------------

	virtual void NativeOnInitialized() override;

	virtual void NativeConstruct() override;

	UFUNCTION(Category="Interaction Widget | Interactable Info")
	float UpdateInteractionProgress();
	

	// PROPERTIES & VARIABLES
	// -----------------------------

	// "BindWidget" makes it so the widget won't compile without the specified UProperty present
	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category="Interaction Widget | Interactable Info")
	UHorizontalBox* InteractionBox;
	
	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category="Interaction Widget | Interactable Info")
	UImage* KeyIcon;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category="Interaction Widget | Interactable Info")
	UTextBlock* ActionText;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category="Interaction Widget | Interactable Info")
	UProgressBar* InteractionProgressBar;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category="Interaction Widget | Interactable Info")
	float InteractionDuration;
};
