#include "TombCeilingDoor.h"

#include "Components/BoxComponent.h"
#include "GameFramework/PlayerController.h"
#include "relic/PlayerCharacter/PCharacter.h"

ATombCeilingDoor::ATombCeilingDoor()
{
	Door = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorMesh"));
	DoorTimelineComp = CreateDefaultSubobject<UTimelineComponent>(TEXT("DoorTimelineComp"));
	DoorSolutionTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("DoorSolutionTrigger"));
	DoorSolutionTrigger->SetVisibility(true);

	Door->SetupAttachment(RootComponent);
	
	DoorTag = "Ceiling";
	Door->ComponentTags.Add(DoorTag);
	this->Tags.Add(DoorTag);
}

void ATombCeilingDoor::BeginPlay()
{
	Super::BeginPlay();

	UpdateFunctionFloatCeiling.BindDynamic(this, &ATombCeilingDoor::UpdateTimelineComp);

	PlayerCharacter = Cast<APCharacter>(GetWorld()->GetGameInstance()->GetFirstLocalPlayerController()->GetPawn());

	if (PlayerCharacter)
	{
		PlayerCharacter->OnMedallionPlaced.AddUObject(this, &ATombCeilingDoor::OnPuzzleSolved);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("TombCeilingDoor: player ref not valid")); 
	}

	if (DoorTimelineCurveFloat)
	{
		DoorTimelineComp->AddInterpFloat(DoorTimelineCurveFloat, UpdateFunctionFloatCeiling);
	}
	
}

void ATombCeilingDoor::UpdateTimelineComp(float Output)
{
	FVector CurrentDoorLocation = this->GetActorLocation();
	
	FVector NewDoorLocation = FVector(Output, CurrentDoorLocation.Y, CurrentDoorLocation.Z);
	Door->SetRelativeLocation(NewDoorLocation);
}

void ATombCeilingDoor::OnPuzzleSolved()
{
	DoorTimelineComp->Play();
}
