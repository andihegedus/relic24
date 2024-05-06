#include "OxygenMeterWidget.h"

#include "Components/HorizontalBox.h"
#include "Components/ProgressBar.h"
#include "relic/PlayerCharacter/PCharacter.h"

void UOxygenMeterWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	PlayerCharacter = Cast<APCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());
}

void UOxygenMeterWidget::NativeConstruct()
{
	Super::NativeConstruct();

	FString FloatToString = FString::FromInt(OxygenPercent);
	
	OxygenPercentText->SetText(FText::FromString(FloatToString));
	WarningText->SetText(FText::FromString("Stable"));
	OxygenProgressBar->SetPercent(100.f);
}

void UOxygenMeterWidget::UpdateWidget(FTimerHandle TimerHandle, float UpdatedPercent)
{
	float TimeRemaining = GetWorld()->GetTimerManager().GetTimerElapsed(TimerHandle);

	OxygenProgressBar->SetPercent(UpdatedPercent/100);
	
	FString FloatToString = FString::FromInt(UpdatedPercent);
	
	OxygenPercentText->SetText(FText::FromString(FloatToString + "%"));

	if (UpdatedPercent >= 75.f)
	{
		WarningText->SetText(FText::FromString("STABLE"));
		OxygenProgressBar->SetFillColorAndOpacity(FLinearColor::Blue);
	}
	else if (UpdatedPercent >= 50.f)
	{
		WarningText->SetText(FText::FromString("MODERATE"));
		OxygenProgressBar->SetFillColorAndOpacity(FLinearColor::Green);
	}
	else if (UpdatedPercent >= 25.f)
	{
		WarningText->SetText(FText::FromString("LOW"));
		OxygenProgressBar->SetFillColorAndOpacity(FLinearColor::Yellow);
	}
	else if (UpdatedPercent >= 2.f)
	{
		WarningText->SetText(FText::FromString("CRITICAL"));
		OxygenProgressBar->SetFillColorAndOpacity(FLinearColor::Red);
	}
	else if (UpdatedPercent == 0.f)
	{
		WarningText->SetText(FText::FromString("OFFLINE"));
	}
	else
	{
		WarningText->SetText(FText::FromString("LOADING"));
		OxygenProgressBar->SetFillColorAndOpacity(FLinearColor::Gray);
	}
}
