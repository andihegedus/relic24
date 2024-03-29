#include "Pickup.h"

#include "Components/SlateWrapperTypes.h"

APickup::APickup()
{
	PrimaryActorTick.bCanEverTick = true;
	
	PickupMeshComp = CreateDefaultSubobject<UStaticMeshComponent>("InstancedMesh");
	SetRootComponent(PickupMeshComp);

	PickupTag = "Pickup";
	PickupMeshComp->ComponentTags.Add(PickupTag);
	this->Tags.Add(PickupTag);
}

void APickup::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void APickup::Interact(APCharacter* PlayerCharacter)
{
	if (PlayerCharacter)
	{
		TakePickup(PlayerCharacter);
	}
}

void APickup::TakePickup(const APCharacter* Taker)
{
	
}

void APickup::BeginPlay()
{
	Super::BeginPlay();
}


