#include "TombStatueDoors.h"

#include "Components/BoxComponent.h"
#include "GameFramework/PlayerController.h"
#include "relic/PlayerCharacter/PCharacter.h"

ATombStatueDoors::ATombStatueDoors()
{
	StatueMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorMesh"));
	DoorTimelineComp = CreateDefaultSubobject<UTimelineComponent>(TEXT("DoorTimelineComp"));
	DoorSolutionTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("DoorSolutionTrigger"));
	DoorSolutionTrigger->SetVisibility(true);

	StatueMeshComp->SetupAttachment(RootComponent);
	
	StatueTag = "Statue";
	StatueMeshComp->ComponentTags.Add(StatueTag);
	this->Tags.Add(StatueTag);
}

void ATombStatueDoors::BeginPlay()
{
	Super::BeginPlay();

	UpdateFunctionFloatCeiling.BindDynamic(this, &ATombStatueDoors::UpdateTimelineComp);

	PlayerCharacter = Cast<APCharacter>(GetWorld()->GetGameInstance()->GetFirstLocalPlayerController()->GetPawn());

	if (PlayerCharacter)
	{
		PlayerCharacter->OnTilePuzzleSolved.AddUObject(this, &ATombStatueDoors::OnPuzzleSolved);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("TombStatueDoors: player ref not valid")); 
	}

	if (DoorTimelineCurveFloat)
	{
		DoorTimelineComp->AddInterpFloat(DoorTimelineCurveFloat, UpdateFunctionFloatCeiling);
	}
}

void ATombStatueDoors::UpdateTimelineComp(float Output)
{
	FVector CurrentDoorLocation = this->GetActorLocation();
	
	FVector NewDoorLocation = FVector(Output - 2600.f, CurrentDoorLocation.Y, CurrentDoorLocation.Z);
	StatueMeshComp->SetRelativeLocation(NewDoorLocation);
}

void ATombStatueDoors::OnPuzzleSolved()
{
	DoorTimelineComp->Play();
}
