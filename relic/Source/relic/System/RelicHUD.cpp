﻿#include "RelicHUD.h"

#include "relic/PlayerCharacter/PCharacter.h"
#include "relic/UserInterface/Interaction/InteractionWidget.h"
#include "relic/UserInterface/Inventory/InventoryWidget.h"
#include "relic/UserInterface/PlayerState/DialogueWidget.h"
#include "relic/UserInterface/PlayerState/OxygenMeterWidget.h"

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
	if (OxygenMeterWidgetClass)
	{
		OxygenMeterWidget = CreateWidget<UOxygenMeterWidget>(GetWorld(), OxygenMeterWidgetClass);
		OxygenMeterWidget->AddToViewport();
		OxygenMeterWidget->SetVisibility(ESlateVisibility::Visible);
	}
	if (DialogueWidgetClass)
	{
		DialogueWidget = CreateWidget<UDialogueWidget>(GetWorld(), DialogueWidgetClass);
		DialogueWidget->AddToViewport();
		DialogueWidget->SetVisibility(ESlateVisibility::Collapsed);
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

void ARelicHUD::UpdateDialogueWidget()
{
	if (DialogueWidget)
	{
		if (DialogueWidget->GetVisibility() == ESlateVisibility::Collapsed)
		{
			DialogueWidget->SetVisibility(ESlateVisibility::Visible);
		}
		if (PlayerCharacter)
		{
			// Might need different array for dialogue triggers
			DialogueWidget->UpdateWidget(PlayerCharacter->TriggerTags);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("HUD: no valid player character found in world.")); 
		}
	}
}

void ARelicHUD::HideDialogueWidget()
{
	if (DialogueWidget)
	{
		DialogueWidget->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void ARelicHUD::ShowOxygenMeterWidget()
{
	if (OxygenMeterWidget)
	{
		OxygenMeterWidget->SetVisibility(ESlateVisibility::Visible);
	}
}

void ARelicHUD::HideOxygenMeterWidget()
{
	if (OxygenMeterWidget)
	{
		OxygenMeterWidget->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void ARelicHUD::ShowDebugWidget()
{
}

void ARelicHUD::HideDebugWidget()
{
}
