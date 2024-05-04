#include "OxygenMeterWidget.h"

#include "Components/HorizontalBox.h"
#include "Components/ProgressBar.h"
#include "relic/PlayerCharacter/PCharacter.h"

void UOxygenMeterWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	/*UpdateFunctionFloat.BindDynamic(this, &UOxygenMeterWidget::UpdateTimelineComp);

	if (MeterTimelineCurveFloat)
	{
		MeterTimelineComp->AddInterpFloat(MeterTimelineCurveFloat, UpdateFunctionFloat);
	}*/

	PlayerCharacter = Cast<APCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());
}

void UOxygenMeterWidget::NativeConstruct()
{
	Super::NativeConstruct();

	FString FloatToString = FString::FromInt(OxygenPercent);
	
	OxygenPercentText->SetText(FText::FromString(FloatToString));
	WarningText->SetText(FText::FromString("Oxygen Levels Stable"));
	OxygenProgressBar->SetPercent(100.f);
}

/*
void UOxygenMeterWidget::UpdateTimelineComp(float Output)
{
	OxygenProgressBar->SetPercent(Output);
}*/

void UOxygenMeterWidget::UpdateWidget(FTimerHandle TimerHandle, float UpdatedPercent)
{
	float TimeRemaining = GetWorld()->GetTimerManager().GetTimerElapsed(TimerHandle);
	
	OxygenProgressBar->SetPercent(TimeRemaining);

	FString FloatToString = FString::FromInt(UpdatedPercent);
	
	OxygenPercentText->SetText(FText::FromString(FloatToString + "%"));

	//MeterTimelineComp->Play();
}
