#include "TileMiniGame.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Camera/CameraComponent.h"
#include "Engine/LocalPlayer.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "relic/PlayerCharacter/PCharacter.h"
#include "relic/PlayerCharacter/PController.h"

ATileMiniGame::ATileMiniGame()
{
	BaseMeshComp = CreateDefaultSubobject<UStaticMeshComponent>("InstancedMesh");
	SetRootComponent(BaseMeshComp);

	TileOne = CreateDefaultSubobject<UStaticMeshComponent>("TileOneMesh");
	TileOne->SetupAttachment(BaseMeshComp);

	TileTwo = CreateDefaultSubobject<UStaticMeshComponent>("TileTwoMesh");
	TileTwo->SetupAttachment(BaseMeshComp);

	TileThree = CreateDefaultSubobject<UStaticMeshComponent>("TileThreeMesh");
	TileThree->SetupAttachment(BaseMeshComp);

	TileFour = CreateDefaultSubobject<UStaticMeshComponent>("TileFourMesh");
	TileFour->SetupAttachment(BaseMeshComp);

	TileFive = CreateDefaultSubobject<UStaticMeshComponent>("TileFiveMesh");
	TileFive->SetupAttachment(BaseMeshComp);

	TileSix = CreateDefaultSubobject<UStaticMeshComponent>("TileSixMesh");
	TileSix->SetupAttachment(BaseMeshComp);

	TileSeven = CreateDefaultSubobject<UStaticMeshComponent>("TileSevenMesh");
	TileSeven->SetupAttachment(BaseMeshComp);

	TileEight = CreateDefaultSubobject<UStaticMeshComponent>("TileEightMesh");
	TileEight->SetupAttachment(BaseMeshComp);

	TileNine = CreateDefaultSubobject<UStaticMeshComponent>("TileNineMesh");
	TileNine->SetupAttachment(BaseMeshComp);

	TileMovement = CreateDefaultSubobject<UFloatingPawnMovement>("MovementComp");

	// Setup PC Camera components
	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArmComp->SetupAttachment(GetRootComponent());
	
	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComp->SetupAttachment(SpringArmComp, USpringArmComponent::SocketName);

	// Assign SpringArm class variables
	SpringArmComp->TargetArmLength = 300.f;

	MiniGameTag = "TileGame";
	BaseMeshComp->ComponentTags.Add(MiniGameTag);
	this->Tags.Add(MiniGameTag);
}

void ATileMiniGame::BeginPlay()
{
	Super::BeginPlay();

	PlayerCharacter = Cast<APCharacter>(GetWorld()->GetGameInstance()->GetFirstLocalPlayerController()->GetPawn());
}

void ATileMiniGame::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent);
	APController* PlayerBaseController = CastChecked<APController>(Controller);

	
	//EnhancedInputComponent->BindAction(PlayerBaseController->DeviceAction, ETriggerEvent::Triggered, this, &ADevice::Move);

	ULocalPlayer* LocalPlayer = PlayerBaseController->GetLocalPlayer();

	check(LocalPlayer);
	UEnhancedInputLocalPlayerSubsystem* Subsystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();

	check(Subsystem);
	Subsystem->ClearAllMappings();
	Subsystem->AddMappingContext(PlayerBaseController->PCMappingContext, 0);
}

void ATileMiniGame::MoveTiles(const FInputActionValue& Value)
{
	//TBD
}

void ATileMiniGame::OnBecomePossessed()
{
	if (PlayerCharacter)
	{
		PlayerCharacter->GetController()->Possess(this);
		AutoPossessPlayer = EAutoReceiveInput::Player0;

		FString CheckController = this->GetController()->GetName();
		
		UE_LOG(LogTemp, Warning, TEXT(" %s "), *CheckController); 

		PlayerController = Cast<APController>(this->Controller);
		
		if (PlayerController)
		{
			PCMappingContext = {PlayerController->PCMappingContext};
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("ADevice: Ref to Player Contoller not valid."));

		}
		
		
		UE_LOG(LogTemp, Warning, TEXT("ADevice: All refs valid. Pawn should be possessed.")); 
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("ADevice: Ref to Player Character not valid.")); 

	}
}

void ATileMiniGame::OnPuzzleSolved()
{
}

void ATileMiniGame::OnPuzzleAbandoned()
{
}


