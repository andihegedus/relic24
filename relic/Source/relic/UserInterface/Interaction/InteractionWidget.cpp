#include "InteractionWidget.h"

#include "Components/HorizontalBox.h"
#include "Components/ProgressBar.h"

void UInteractionWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	InteractionProgressBar->PercentDelegate.BindUFunction(this, "UpdateInteractionProgress");
}

void UInteractionWidget::NativeConstruct()
{
	Super::NativeConstruct();

	ActionText->SetText(FText::FromString("Press"));
	ResultText->SetText(FText::FromString("to take item."));
	InteractionDuration = 0.0f;
}

void UInteractionWidget::UpdateWidget(const TArray<FName> Tags)
{
	if (Tags.Num() > 0)
	{
		if (Tags.Contains("Pickup"))
		{
			UE_LOG(LogTemp, Warning, TEXT("Interaction Widget should be visible now."));
			InteractionBox->SetVisibility(ESlateVisibility::Visible);
			KeyIcon->SetVisibility(ESlateVisibility::Visible);
			ActionText->SetText(FText::FromString("Press"));
			ResultText->SetText(FText::FromString("to pickup item."));
			InteractionProgressBar->SetVisibility(ESlateVisibility::Collapsed);
		}
		if (Tags.Contains("Device"))
		{
			KeyIcon->SetVisibility(ESlateVisibility::Visible);
			ActionText->SetText(FText::FromString("Hold"));
			InteractionProgressBar->SetVisibility(ESlateVisibility::Visible);
		}
		if (Tags.Contains("Slot"))
		{
			KeyIcon->SetVisibility(ESlateVisibility::Visible);
			ActionText->SetText(FText::FromString("Press"));
			InteractionProgressBar->SetVisibility(ESlateVisibility::Visible);
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("UInteractionWidget: No Component Tags detected. Can't update widget.")); 
	}
}

float UInteractionWidget::UpdateInteractionProgress()
{
	return 0.0f;
}
