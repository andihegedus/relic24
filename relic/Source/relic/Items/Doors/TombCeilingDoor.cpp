#include "TombCeilingDoor.h"

#include "Components/ActorComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/GameStateBase.h"
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

	TArray<AActor*> OverlappingActors;
	GetWorld()->GetGameState()->GetOverlappingActors(OverlappingActors);

	for (int i = 1; i < OverlappingActors.Num(); i++)
	{
		if (OverlappingActors[i]->Tags.Contains("Player"))
		{
			Player = Cast<APCharacter>(OverlappingActors[i]);

			if (Player)
			{
				Player->OnMedallionPlaced.AddUObject(this, &ATombCeilingDoor::OnPuzzleSolved);
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("Ceiling: player not valid")); 

			}
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Ceiling: Player not found in overlap radius.")); 
		}
	}
	

	if (DoorTimelineCurveFloat)
	{
		DoorTimelineComp->AddInterpFloat(DoorTimelineCurveFloat, UpdateFunctionFloatCeiling);
	}
	
	
	//DoorSolutionTrigger->OnComponentBeginOverlap.AddDynamic(this, &ATombCeilingDoor::OnOverlapBegin);
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

/*void ATombCeilingDoor::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* Actor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	DoorTimelineComp->Play();
}*/
