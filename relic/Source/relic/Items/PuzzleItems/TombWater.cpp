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
		PlayerCharacter->OnCheckpointReached.AddUObject(this, &ATombWater::RaiseWaterLevel);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("ATombWater: Ref to Player Character not valid."));
	}

	UpdateFunctionFloat.BindDynamic(this, &ATombWater::UpdateTimelineComp);

	if (WaterTimelineCurveFloat)
	{
		WaterTimelineComp->AddInterpFloat(WaterTimelineCurveFloat, UpdateFunctionFloat);
	}

	WaterProxTrigger->OnComponentBeginOverlap.AddDynamic(this, &ATombWater::OnOverlapBegin);
}

void ATombWater::UpdateTimelineComp(float Output)
{
	switch (WaterLevelID)
	{
		case 1:
			UE_LOG(LogTemp, Warning, TEXT("ATombWater: Case 1 Triggered."));
			LevelOneWater = FVector(-2660.f, 260.f, Output - 2450.f);
			WaterMeshComp->SetRelativeLocation(LevelOneWater);
			break;
		case 2:
			LevelTwoWater = FVector(LevelOneWater.X, LevelOneWater.Y, Output - 2350.f);
			WaterMeshComp->SetRelativeLocation(LevelTwoWater);
			break;
		case 3:
			LevelThreeWater = FVector(LevelOneWater.X, LevelOneWater.Y, Output - 1650.f);
			WaterMeshComp->SetRelativeLocation(LevelThreeWater);
			break;
		default:
			UE_LOG(LogTemp, Warning, TEXT("ATombWater: Default Case Triggered."));
			break;
	}
}

void ATombWater::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* Actor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	WaterLevelID = 1;
	RaiseWaterLevel();
}

void ATombWater::RaiseWaterLevel()
{
	if (PlayerCharacter)
	{
		WaterLevelID = PlayerCharacter->WaterLevelID;
	}
	
	WaterTimelineComp->Play();
}
