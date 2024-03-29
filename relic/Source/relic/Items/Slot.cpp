#include "Slot.h"


ASlot::ASlot()
{
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
