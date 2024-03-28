#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "RelicHUD.generated.h"

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

	void ShowDialogueWidget();
	void HideDialogueWidget();

	// Might not need these, placeholder for now:
	//void ShowCrosshair();
	//void HideCrosshair();

	void ShowDebugWidget();
	void HideDebugWidget();
	

	// PROPERTIES & VARIABLES
	// -----------------------------

	bool bIsMenuVisible;
	bool bIsWidgetVisible;

protected:
	// PROPERTIES & VARIABLES
	// -----------------------------

	// MainMenuWidget
	// InteractionWidget
	// DialogueWidget
	// CrosshairWidget
	// DebugWidget
};
