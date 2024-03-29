#include "Slot.h"


ASlot::ASlot()
{
	PrimaryActorTick.bCanEverTick = true;
	
	SlotMeshComp = CreateDefaultSubobject<UStaticMeshComponent>("InstancedMesh");
	SetRootComponent(SlotMeshComp);

	SlotTag = "Slot";
	SlotMeshComp->ComponentTags.Add(SlotTag);
	this->Tags.Add(SlotTag);
}

void ASlot::BeginPlay()
{
	Super::BeginPlay();

	SetActorHiddenInGame(true);
}

void ASlot::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}
