#include "Pickup.h"

#include "Components/BoxComponent.h"

APickup::APickup()
{
	PickupMeshComp = CreateDefaultSubobject<UStaticMeshComponent>("InstancedMesh");
	SetRootComponent(PickupMeshComp);

	BoxCollision = CreateDefaultSubobject<UBoxComponent>("Collision");
	BoxCollision->SetupAttachment(PickupMeshComp);
	
	PickupTag = "Pickup";
	PickupMeshComp->ComponentTags.Add(PickupTag);
	this->Tags.Add(PickupTag);
}

void APickup::BeginPlay()
{
	Super::BeginPlay();
}





