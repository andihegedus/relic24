#include "OxygenMeterWidget.h"

#include "Components/BrushComponent.h"
#include "Components/HorizontalBox.h"
#include "Components/ProgressBar.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "relic/PlayerCharacter/PCharacter.h"

void UOxygenMeterWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	
	PlayerCharacter = Cast<APCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());
	RoundBarMatInstDynamic = UMaterialInstanceDynamic::Create(RoundBarMaterial, this);
}

void UOxygenMeterWidget::NativeConstruct()
{
	Super::NativeConstruct();

	FString FloatToString = FString::FromInt(OxygenPercent);
	
	OxygenPercentText->SetText(FText::FromString(FloatToString));
	WarningText->SetText(FText::FromString("Stable"));
	OxygenProgressBar->SetPercent(100.f);
}


void UOxygenMeterWidget::SetRoundPBPercent(float Percent)
{
	if (RoundBarMatInstDynamic)
	{
		//UE_LOG(LogTemp, Warning, TEXT("UOxygenMeterWidget: Dynamic Material Instance valid!"));
	
		RoundBarMatInstDynamic->SetScalarParameterValue("Percentage", Percent);
		RoundBarImage->SetBrushFromMaterial(RoundBarMatInstDynamic);

		if (Percent >= .75f)
		{
			RoundBarImage->SetColorAndOpacity(FLinearColor::Blue);
		}
		else if (Percent >= .50f)
		{
			RoundBarImage->SetColorAndOpacity(FLinearColor::Blue);
		}
		else if (Percent >= .25f)
		{
			RoundBarImage->SetColorAndOpacity(FLinearColor::Yellow);
		}
		else if (Percent >= 0.f)
		{
			RoundBarImage->SetColorAndOpacity(FLinearColor::Red);
		}
		else if (Percent < 0.f)
		{
			RoundBarImage->SetColorAndOpacity(FLinearColor::Gray);
		}
		

		FHashedMaterialParameterInfo ParameterInfo;
	
		RoundBarMatInstDynamic->GetScalarParameterValue(ParameterInfo, Percent);

		FString PercentString = FString::FromInt(Percent);
	
		//UE_LOG(LogTemp, Warning, TEXT("%s"), *PercentString);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("UOxygenMeterWidget: Dynamic Material Instance not valid. :("));
	}
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
		//OxygenProgressBar->SetFillColorAndOpacity(FLinearColor::Blue);
	}
	else if (UpdatedPercent >= 50.f)
	{
		WarningText->SetText(FText::FromString("MODERATE"));
		//OxygenProgressBar->SetFillColorAndOpacity(FLinearColor::Green);
	}
	else if (UpdatedPercent >= 25.f)
	{
		WarningText->SetText(FText::FromString("LOW"));
		//OxygenProgressBar->SetFillColorAndOpacity(FLinearColor::Yellow);
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
		WarningText->SetText(FText::FromString("OFFLINE"));
		//OxygenProgressBar->SetFillColorAndOpacity(FLinearColor::Gray);
	}
}
