#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "RelicHUD.generated.h"

class UDialogueWidget;
class UOxygenMeterWidget;
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

	void UpdateDialogueWidget();
	void HideDialogueWidget();

	void ShowOxygenMeterWidget();
	void HideOxygenMeterWidget();

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

	UPROPERTY(EditDefaultsOnly, Category="Widgets")
	TSubclassOf<UOxygenMeterWidget> OxygenMeterWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category="Widgets")
	TSubclassOf<UDialogueWidget> DialogueWidgetClass;

	// Need to be public so they can be accessed by our PCharacter class
	UPROPERTY()
	UInteractionWidget* InteractionWidget;

	UPROPERTY(EditDefaultsOnly, Category="Widgets")
	UOxygenMeterWidget* OxygenMeterWidget;
	
	UPROPERTY()
	UDialogueWidget* DialogueWidget;

protected:
	// PROPERTIES & VARIABLES
	// -----------------------------

	// MainMenuWidget
	
	UPROPERTY()
	UInventoryWidget* InventoryWidget;
	
	// CrosshairWidget
	// DebugWidget
};
