#include "InventoryWidget.h"

#include "relic/PlayerCharacter/PCharacter.h"


void UInventoryWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	PlayerCharacter = Cast<APCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());
}

void UInventoryWidget::NativeConstruct()
{
	Super::NativeConstruct();

	QuantityText->SetText(FText::FromString("null"));
}


void UInventoryWidget::UpdateWidget(const TArray<FName> Tags)
{
	if (Tags.Num() > 0)
	{
		if (Tags.Contains("Pickup"))
		{
			ItemIcon->SetVisibility(ESlateVisibility::Visible);

			if (PlayerCharacter)
			{
			    // Add "+1" to player inventory quantity because the quantity resets after the pickup action is completed
			    // Otherwise, this text number will always be 1 item behind
				FString QuantityAsString = FString::FromInt(PlayerCharacter->InventoryQuantity + 1);
				QuantityText->SetText(FText::FromString(QuantityAsString));
				
				QuantityText->SetVisibility(ESlateVisibility::Visible);
				
				if (PlayerCharacter->InventoryQuantity + 1 <= 1)
				{
					QuantityText->SetVisibility(ESlateVisibility::Collapsed);
				}
				else
				{
				    QuantityText->SetVisibility(ESlateVisibility::Visible);
				}
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("Player character not valid."));
			}
			
		}
		if (Tags.Contains("Slot"))
        {
            
            if (PlayerCharacter)
            {
                if (PlayerCharacter->InventoryQuantity <= 0)
                {
                    ItemIcon->SetVisibility(ESlateVisibility::Collapsed);
                }
                FString QuantityAsString = FString::FromInt(PlayerCharacter->InventoryQuantity + 1);
                QuantityText->SetText(FText::FromString(QuantityAsString));
                
                QuantityText->SetVisibility(ESlateVisibility::Visible);
                
                if (PlayerCharacter->InventoryQuantity <= 1)
                {
                    QuantityText->SetVisibility(ESlateVisibility::Collapsed);
                }
                else
                {
                    QuantityText->SetVisibility(ESlateVisibility::Visible);
                }
            }
            else
            {
                UE_LOG(LogTemp, Warning, TEXT("Player character not valid."));
            }
            
        }
	}
}
