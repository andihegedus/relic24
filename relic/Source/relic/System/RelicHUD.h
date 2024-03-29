#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "RelicHUD.generated.h"

class UInventoryWidget;
class APCharacter;
class UInteractionWidget;

UCLASS()
class RELIC_API ARelicHUD : public AHUD
{
	GENERATED_BODY()
	
public:
	// FUNCTIONS
	// -----------------------------

	ARelicHUD();

	virtual void BeginPlay() override;

	void ShowMainMenu();
	void HideMainMenu();

	
	void HideInteractionWidget();
	void UpdateInteractionWidget(const FName Tag) const;

	void HideInventoryWidget();
	void UpdateInventoryWidget(const FName Tag) const;

	void ShowDialogueWidget();
	void HideDialogueWidget();

	// Might not need these, placeholder for now:
	//void ShowCrosshair();
	//void HideCrosshair();

	void ShowDebugWidget();
	void HideDebugWidget();
	

	// PROPERTIES & VARIABLES
	// -----------------------------

	UPROPERTY()
	APCharacter* PlayerCharacter;

	bool bIsMenuVisible;
	bool bIsWidgetVisible;

	UPROPERTY(EditDefaultsOnly, Category="Widgets")
	TSubclassOf<UInteractionWidget> InteractionWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category="Widgets")
	TSubclassOf<UInventoryWidget> InventoryWidgetClass;

	UPROPERTY()
	UInteractionWidget* InteractionWidget;

protected:
	// PROPERTIES & VARIABLES
	// -----------------------------

	// MainMenuWidget

	
	
	UPROPERTY()
	UInventoryWidget* InventoryWidget;
	
	// DialogueWidget
	// CrosshairWidget
	// DebugWidget
};
