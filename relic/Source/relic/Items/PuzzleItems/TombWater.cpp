#include "TombWater.h"

#include "Components/BoxComponent.h"
#include "GameFramework/PlayerController.h"
#include "relic/PlayerCharacter/PCharacter.h"

ATombWater::ATombWater()
{
	WaterMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WaterMesh"));
	SetRootComponent(WaterMeshComp);
	WaterTimelineComp = CreateDefaultSubobject<UTimelineComponent>(TEXT("WaterTimelineComp"));
	WaterProxTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("WaterProximityTigger"));
	WaterProxTrigger->AttachToComponent(WaterMeshComp, FAttachmentTransformRules::KeepRelativeTransform);

	InitialWaterLocation = this->GetActorLocation();
}

void ATombWater::BeginPlay()
{
	Super::BeginPlay();

	PlayerCharacter = Cast<APCharacter>(GetWorld()->GetGameInstance()->GetFirstLocalPlayerController()->GetPawn());

	if (PlayerCharacter)
	{
		PlayerCharacter->OnTilePuzzleSolved.AddUObject(this, &ATombWater::RaiseWaterLevel);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("ATombWater: Ref to Player Character not valid."));
	}
}

void ATombWater::UpdateTimelineComp(float Output)
{
	switch (WaterLevelID)
	{
		case 1:
			LevelOneWater = FVector(InitialWaterLocation.X, InitialWaterLocation.Y, Output);
			WaterMeshComp->SetRelativeLocation(LevelOneWater);
			break;
		case 2:
			LevelTwoWater = FVector(LevelOneWater.X, LevelOneWater.Y, Output);
			WaterMeshComp->SetRelativeLocation(LevelTwoWater);
			break;
		case 3:
			LevelThreeWater = FVector(LevelTwoWater.X, LevelTwoWater.Y, Output);
			WaterMeshComp->SetRelativeLocation(LevelThreeWater);
			break;
		default:
			break;
	}
}

void ATombWater::RaiseWaterLevel()
{
	WaterTimelineComp->Play();
}
