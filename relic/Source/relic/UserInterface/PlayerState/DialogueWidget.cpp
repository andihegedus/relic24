#include "DialogueWidget.h"

#include "Components/HorizontalBox.h"
#include "Components/TextBlock.h"

void UDialogueWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
}

void UDialogueWidget::NativeConstruct()
{
	Super::NativeConstruct();

	DialogueText->SetText(FText::FromString("..."));
	ActionText->SetText(FText::FromString(" "));
	EffectText->SetText(FText::FromString(" "));
}

void UDialogueWidget::UpdateWidget(const TArray<FName> Tags)
{
	if (Tags.Num() > 0)
	{
		if (Tags.Contains("Begin"))
		{
			DialogueText->SetText(FText::FromString("So this is it? This is \"The Great Isle\"? ...doesn't seem so special. It looks just like all the other places we searched."));
			ActionText->SetText(FText::FromString("Press"));
			EffectText->SetText(FText::FromString("Close"));
		}
		if (Tags.Contains("Entrance"))
		{
			DialogueText->SetText(FText::FromString("Oh... No. \"Great\" as in vast. Big. Way, way too big..."));
			ActionText->SetText(FText::FromString("Press"));
			EffectText->SetText(FText::FromString("Close"));
		}
	}
}
