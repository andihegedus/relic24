﻿#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InteractionWidget.generated.h"

class APCharacter;
class APickup;
class UProgressBar;
class UTextBlock;
class UImage;
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

	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category="Interaction Widget | Interactable Info")
	UProgressBar* InteractionProgressBar;


protected:
	// FUNCTIONS
	// -----------------------------

	virtual void NativeOnInitialized() override;

	virtual void NativeConstruct() override;
	

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
	UTextBlock* ResultText;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category="Interaction Widget | Interactable Info")
	float InteractionDuration;
};
