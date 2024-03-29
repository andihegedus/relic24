#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "InventoryWidget.generated.h"

class APCharacter;
class APickup;
class UHorizontalBox;
class UVerticalBox;
class UTextBlock;

UCLASS()
class UInventoryWidget : public UUserWidget
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


	// PROPERTIES & VARIABLES
	// -----------------------------

	// "BindWidget" makes it so the widget won't compile without the specified UProperty present
	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category="Inventory Widget | Inventory Info")
	UVerticalBox* InventoryBox;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category="Inventory Widget | Inventory Info")
	UHorizontalBox* SlotBox;
	
	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category="Inventory Widget | Inventory Info")
	UImage* ItemIcon;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category="Inventory Widget | Inventory Info")
	UTextBlock* QuantityText;

	//UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category="Inventory Widget | Inventory Info")
	//int32 InventoryQuantity;
	
};
