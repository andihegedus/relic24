#include "RelicHUD.h"

#include "relic/PlayerCharacter/PCharacter.h"
#include "relic/UserInterface/Interaction/InteractionWidget.h"
#include "relic/UserInterface/Inventory/InventoryWidget.h"

ARelicHUD::ARelicHUD()
{
}

void ARelicHUD::BeginPlay()
{
	Super::BeginPlay();

	if (InteractionWidgetClass)
	{
		InteractionWidget = CreateWidget<UInteractionWidget>(GetWorld(), InteractionWidgetClass);
		InteractionWidget->AddToViewport(); 
		InteractionWidget->SetVisibility(ESlateVisibility::Collapsed);
	}
	if (InventoryWidgetClass)
	{
		InventoryWidget = CreateWidget<UInventoryWidget>(GetWorld(), InventoryWidgetClass);
		InventoryWidget->AddToViewport(); 
		InventoryWidget->SetVisibility(ESlateVisibility::Collapsed);
	}
	

	PlayerCharacter = Cast<APCharacter>(GetOwningPawn());
}

void ARelicHUD::ShowMainMenu()
{
}

void ARelicHUD::HideMainMenu()
{
}

void ARelicHUD::HideInteractionWidget()
{
	if (InteractionWidget)
	{
		InteractionWidget->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void ARelicHUD::UpdateInteractionWidget(const FName Tag) const
{
	if (InteractionWidget)
	{
		if (InteractionWidget->GetVisibility() == ESlateVisibility::Collapsed)
		{
			InteractionWidget->SetVisibility(ESlateVisibility::Visible);
		}
		if (PlayerCharacter)
		{
			InteractionWidget->UpdateWidget(PlayerCharacter->TagInFocus);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("HUD: no valid player character found in world.")); 
		}
	}
}

void ARelicHUD::HideInventoryWidget()
{
	if (InventoryWidget)
	{
		InventoryWidget->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void ARelicHUD::UpdateInventoryWidget(const FName Tag) const
{
	if (InventoryWidget)
	{
		if (InventoryWidget->GetVisibility() == ESlateVisibility::Collapsed)
		{
			InventoryWidget->SetVisibility(ESlateVisibility::Visible);
		}
		if (PlayerCharacter)
		{
			InventoryWidget->UpdateWidget(PlayerCharacter->TagInFocus);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("HUD: no valid player character found in world.")); 
		}
	}
}

void ARelicHUD::ShowDialogueWidget()
{
}

void ARelicHUD::HideDialogueWidget()
{
}

void ARelicHUD::ShowDebugWidget()
{
}

void ARelicHUD::HideDebugWidget()
{
}
