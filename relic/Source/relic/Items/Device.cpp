#include "Device.h"

#include "GameFramework/PlayerController.h"
#include "relic/PlayerCharacter/PCharacter.h"

ADevice::ADevice()
{
	DeviceMeshComp = CreateDefaultSubobject<UStaticMeshComponent>("InstancedMesh");
	DeviceTimelineComp = CreateDefaultSubobject<UTimelineComponent>(TEXT("DeviceTimelineComp"));
	SetRootComponent(DeviceMeshComp);

	DeviceTag = "Device";
	DeviceMeshComp->ComponentTags.Add(DeviceTag);
	this->Tags.Add(DeviceTag);
}

void ADevice::BeginPlay()
{
	Super::BeginPlay();

	UpdateFunctionFloatCeiling.BindDynamic(this, &ADevice::UpdateTimelineComp);

	PlayerCharacter = Cast<APCharacter>(GetWorld()->GetGameInstance()->GetFirstLocalPlayerController()->GetPawn());

	if (PlayerCharacter)
	{
		PlayerCharacter->OnDeviceActivated.AddUObject(this, &ADevice::OnPuzzleSolved);
		PlayerCharacter->OnDeviceAbandoned.AddUObject(this, &ADevice::OnPuzzleAbandoned);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("TombCeilingDoor: player ref not valid")); 
	}

	if (DeviceTimelineCurveFloat)
	{
		DeviceTimelineComp->AddInterpFloat(DeviceTimelineCurveFloat, UpdateFunctionFloatCeiling);
	}
}

void ADevice::UpdateTimelineComp(float Output)
{
	FRotator CurrentDeviceRotation = this->GetActorRotation();
	
	FRotator NewDeviceRotation = FRotator(Output, CurrentDeviceRotation.Yaw, CurrentDeviceRotation.Roll);
	DeviceMeshComp->SetRelativeRotation(NewDeviceRotation);
}

void ADevice::OnPuzzleSolved()
{
	
	// potentially pawn possession here?
	
	DeviceTimelineComp->Play();

	if (!DeviceTimelineComp->IsPlaying())
	{
		Destroy();
	}
	
}

void ADevice::OnPuzzleAbandoned()
{
	DeviceTimelineComp->Reverse();
}	
	


