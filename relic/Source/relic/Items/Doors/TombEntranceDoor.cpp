#include "TombEntranceDoor.h"

#include "Components/BoxComponent.h"
#include "Components/TimelineComponent.h"

ATombEntranceDoor::ATombEntranceDoor()
{
	Door = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorMesh"));
	DoorTimelineComp = CreateDefaultSubobject<UTimelineComponent>(TEXT("DoorTimelineComp"));
	DoorProxTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("DoorProximityTigger"));

	Door->SetupAttachment(RootComponent);
	DoorProxTrigger->AttachToComponent(Door, FAttachmentTransformRules::KeepRelativeTransform);
}

void ATombEntranceDoor::BeginPlay()
{
	Super::BeginPlay();

	UpdateFunctionFloat.BindDynamic(this, &ATombEntranceDoor::UpdateTimelineComp);

	if (DoorTimelineCurveFloat)
	{
		DoorTimelineComp->AddInterpFloat(DoorTimelineCurveFloat, UpdateFunctionFloat);
	}

	DoorProxTrigger->OnComponentBeginOverlap.AddDynamic(this, &ATombEntranceDoor::OnOverlapBegin);
	//DoorProxTrigger->OnComponentEndOverlap.AddDynamic(this, &ATombEntranceDoor::OnOverlapEnd);
}

void ATombEntranceDoor::UpdateTimelineComp(float Output)
{
	FVector CurrentDoorLocation = this->GetActorLocation();
	
	FVector NewDoorLocation = FVector(Output, CurrentDoorLocation.Y, CurrentDoorLocation.Z);
	Door->SetRelativeLocation(NewDoorLocation);
}

void ATombEntranceDoor::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* Actor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	DoorTimelineComp->Play();
}

void ATombEntranceDoor::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* Actor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex)
{
	// save this for later, using different trigger
	//DoorTimelineComp->Reverse();
}
