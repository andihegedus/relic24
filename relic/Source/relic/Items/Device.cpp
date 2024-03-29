#include "Device.h"

ADevice::ADevice()
{
	DeviceMeshComp = CreateDefaultSubobject<UStaticMeshComponent>("InstancedMesh");
	SetRootComponent(DeviceMeshComp);

	DeviceTag = "Device";
	DeviceMeshComp->ComponentTags.Add(DeviceTag);
	this->Tags.Add(DeviceTag);
}

void ADevice::BeginPlay()
{
	Super::BeginPlay();
}
