#include "RelicHUD.h"

#include "relic/PlayerCharacter/PCharacter.h"
#include "relic/UserInterface/Interaction/InteractionWidget.h"

ARelicHUD::ARelicHUD()
{
}

void ARelicHUD::BeginPlay()
{
	Super::BeginPlay();

	if (InteractionWidgetClass)
	{
		UE_LOG(LogTemp, Warning, TEXT("Interaction widget valid"));
		InteractionWidget = CreateWidget<UInteractionWidget>(GetWorld(), InteractionWidgetClass);
		InteractionWidget->AddToViewport(); 
		InteractionWidget->SetVisibility(ESlateVisibility::Collapsed);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Interaction widget class not found."));
	}

	PlayerCharacter = Cast<APCharacter>(GetOwningPawn());
}

void ARelicHUD::ShowMainMenu()
{
}

void ARelicHUD::HideMainMenu()
{
}

void ARelicHUD::ShowInteractionWidget()
{
	if (InteractionWidget)
	{
		InteractionWidget->SetVisibility(ESlateVisibility::Visible);
	}
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
			
		}
		
		InteractionWidget->SetVisibility(ESlateVisibility::Visible);

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
