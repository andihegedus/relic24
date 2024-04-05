#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DialogueWidget.generated.h"


class UImage;
class UButton;
class APCharacter;
class UProgressBar;
class UTextBlock;
class UHorizontalBox;

UCLASS()
class RELIC_API UDialogueWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	// FUNCTIONS
	// -----------------------------
	void UpdateWidget(const TArray<FName> Tags);


	// PROPERTIES & VARIABLES
	// -----------------------------

	UPROPERTY()
	APCharacter* PlayerCharacter;


	protected:
	// FUNCTIONS
	// -----------------------------

	virtual void NativeOnInitialized() override;

	virtual void NativeConstruct() override;
	

	// PROPERTIES & VARIABLES
	// -----------------------------

	// "BindWidget" makes it so the widget won't compile without the specified UProperty present
	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category="Dialogue Widget | Dialogue Info")
	UHorizontalBox* DialogueBox;
	
	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category="Dialogue Widget | Dialogue Info")
	UImage* ContinueDialogueIcon;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category="Dialogue Widget | Dialogue Info")
	UTextBlock* DialogueText;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category="Dialogue Widget | Dialogue Info")
	UTextBlock* ActionText;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category="Dialogue Widget | Dialogue Info")
	UTextBlock* EffectText;
};
