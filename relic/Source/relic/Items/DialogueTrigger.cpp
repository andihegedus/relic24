#include "DialogueTrigger.h"

#include "Components/BoxComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "relic/PlayerCharacter/PCharacter.h"
#include "relic/System/RelicHUD.h"

ADialogueTrigger::ADialogueTrigger()
{
	DialogueProxTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("DialogueProximityTrigger"));

	Tags.Add("Dialogue");
	Tags.Add(TriggerTag);
}

void ADialogueTrigger::BeginPlay()
{
	Super::BeginPlay();

	HUD = Cast<ARelicHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());

	PlayerCharacter = Cast<APCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());

	DialogueProxTrigger->OnComponentBeginOverlap.AddDynamic(this, &ADialogueTrigger::OnOverlapBegin);

	if (PlayerCharacter)
	{
		PlayerCharacter->OnEnterButtonPressed.AddUObject(this, &ADialogueTrigger::CloseAndDestroy);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("ADialogueTriggerr: PlayerCharacter ref not valid."));
	}
	
}

void ADialogueTrigger::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* Actor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (PlayerCharacter)
	{
		PlayerCharacter->TriggerTags.Add(TriggerTag);
		PlayerCharacter->GetCharacterMovement()->Deactivate();
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("ADialogueTrigger: PlayerCharacter ref not valid."));
	}
	
	HUD->UpdateDialogueWidget();
}


void ADialogueTrigger::CloseAndDestroy()
{
	HUD->HideDialogueWidget();

	if (PlayerCharacter)
	{
		// This is probably a bit overkill, I think I can simplify this system later
		switch (LocationID)
		{
			case 1:
				if (PlayerCharacter->TriggerTags.Contains("Begin")){ Destroy(); }
				else { UE_LOG(LogTemp, Warning, TEXT("ADialogueTrigger: Begin trigger tag not found.")); }
				break;
			case 2:
				if (PlayerCharacter->TriggerTags.Contains("Entrance")){ Destroy(); }
				else { UE_LOG(LogTemp, Warning, TEXT("ADialogueTrigger: Entrance trigger tag not found.")); }
				break;
			default:
				UE_LOG(LogTemp, Warning, TEXT("ADialogueTrigger: Trigger tag not found."));
				break;
		}  
		PlayerCharacter->GetCharacterMovement()->Activate();
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("ADialogueTrigger: PlayerCharacter ref not valid."));
	}
}
