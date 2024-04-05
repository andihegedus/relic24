#include "Pickup.h"

APickup::APickup()
{
	PickupMeshComp = CreateDefaultSubobject<UStaticMeshComponent>("InstancedMesh");
	SetRootComponent(PickupMeshComp);

	PickupTag = "Pickup";
	PickupMeshComp->ComponentTags.Add(PickupTag);
	this->Tags.Add(PickupTag);
}

void APickup::BeginPlay()
{
	Super::BeginPlay();
}





