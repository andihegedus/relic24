#include "InteractionWidget.h"

#include "Components/HorizontalBox.h"
#include "Components/ProgressBar.h"
#include "relic/PlayerCharacter/PCharacter.h"

void UInteractionWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
}

void UInteractionWidget::NativeConstruct()
{
	Super::NativeConstruct();

	ActionText->SetText(FText::FromString("Press"));
	ResultText->SetText(FText::FromString("to take item."));
	InteractionProgressBar->SetPercent(0.f);
}

void UInteractionWidget::UpdateWidget(const TArray<FName> Tags)
{
	if (Tags.Num() > 0)
	{
		if (Tags.Contains("Pickup"))
		{
			KeyIcon->SetVisibility(ESlateVisibility::Visible);
			ActionText->SetText(FText::FromString("Press"));
			ResultText->SetText(FText::FromString("to pickup item."));
			InteractionProgressBar->SetVisibility(ESlateVisibility::Collapsed);
		}
		if (Tags.Contains("Device"))
		{
			KeyIcon->SetVisibility(ESlateVisibility::Visible);
			ActionText->SetText(FText::FromString("Hold"));
			ResultText->SetText(FText::FromString("to turn dial."));
			InteractionProgressBar->SetVisibility(ESlateVisibility::Visible);
		}
		if (Tags.Contains("Slot"))
		{
			KeyIcon->SetVisibility(ESlateVisibility::Visible);
			ActionText->SetText(FText::FromString("Press"));
			ResultText->SetText(FText::FromString("to place medallion."));
			InteractionProgressBar->SetVisibility(ESlateVisibility::Collapsed);
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("UInteractionWidget: No Component Tags detected. Can't update widget.")); 
	}
}
