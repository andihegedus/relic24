#include "CeilingDoorAndSlots.h"

ACeilingDoorAndSlots::ACeilingDoorAndSlots()
{
	DoorMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorMesh"));
	SlotMeshComp = CreateDefaultSubobject<UStaticMeshComponent>("Slot1Mesh");
	DoorTimelineComp = CreateDefaultSubobject<UTimelineComponent>(TEXT("DoorTimelineComp"));
	DoorSolutionTrigger = CreateDefaultSubobject<UActorComponent>(TEXT("DoorSolutionTrigger"));

	DoorMeshComp->SetupAttachment(RootComponent);
	SlotMeshComp->AttachToComponent(DoorMeshComp, FAttachmentTransformRules::KeepRelativeTransform);

	SlotMeshComp->SetVisibility(false);
	
	DoorTag = "Slot";
	DoorMeshComp->ComponentTags.Add(DoorTag);
	this->Tags.Add(DoorTag);
}

void ACeilingDoorAndSlots::BeginPlay()
{
	Super::BeginPlay();

	UpdateFunctionFloatCeiling.BindDynamic(this, &ACeilingDoorAndSlots::UpdateTimelineComp);

	if (DoorTimelineCurveFloat)
	{
		DoorTimelineComp->AddInterpFloat(DoorTimelineCurveFloat, UpdateFunctionFloatCeiling);
	}

	DoorSolutionTrigger->OnComponentActivated.AddDynamic(this, &ACeilingDoorAndSlots::OnTriggerPuzzleSolution);
}

void ACeilingDoorAndSlots::UpdateTimelineComp(float Output)
{
	FVector CurrentDoorLocation = this->GetActorLocation();
	
	FVector NewDoorLocation = FVector(Output, CurrentDoorLocation.Y, CurrentDoorLocation.Z);
	DoorMeshComp->SetRelativeLocation(NewDoorLocation);
}

void ACeilingDoorAndSlots::OnTriggerPuzzleSolution(UActorComponent* ActorComp, bool bIsTriggered)
{
	SlotMeshComp->SetVisibility(true);
	DoorTimelineComp->Play();
	UE_LOG(LogTemp, Warning, TEXT("Ceiling Play button triggered.")); 
}
