#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "RelicHUD.generated.h"

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

	void ShowInteractionWidget();
	void HideInteractionWidget();
	void UpdateInteractionWidget(const FName Tag) const;

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

protected:
	// PROPERTIES & VARIABLES
	// -----------------------------

	// MainMenuWidget

	UPROPERTY()
	UInteractionWidget* InteractionWidget;
	
	// DialogueWidget
	// CrosshairWidget
	// DebugWidget
};
