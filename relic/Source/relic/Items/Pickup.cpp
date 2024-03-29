#include "Pickup.h"

#include "relic/PlayerCharacter/PCharacter.h"

APickup::APickup()
{
	PrimaryActorTick.bCanEverTick = true;
	
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

void APickup::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}




