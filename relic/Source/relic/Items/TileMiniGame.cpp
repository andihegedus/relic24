#include "TileMiniGame.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Camera/CameraComponent.h"
#include "Components/Slider.h"
#include "Engine/LocalPlayer.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "relic/PlayerCharacter/PCharacter.h"
#include "relic/PlayerCharacter/PController.h"
#include "relic/System/RelicHUD.h"
#include "Widgets/Text/SlateEditableTextTypes.h"

ATileMiniGame::ATileMiniGame()
{
	BaseMeshComp = CreateDefaultSubobject<UStaticMeshComponent>("InstancedMesh");
	SetRootComponent(BaseMeshComp);

	// TODO: There's probably a cleaner way to do this
	TileOne = CreateDefaultSubobject<UStaticMeshComponent>("TileOneMesh");
	TileOne->SetupAttachment(BaseMeshComp);
	Tiles.Add(TileOne);

	TileTwo = CreateDefaultSubobject<UStaticMeshComponent>("TileTwoMesh");
	TileTwo->SetupAttachment(BaseMeshComp);
	Tiles.Add(TileTwo);

	TileThree = CreateDefaultSubobject<UStaticMeshComponent>("TileThreeMesh");
	TileThree->SetupAttachment(BaseMeshComp);
	Tiles.Add(TileThree);

	TileFour = CreateDefaultSubobject<UStaticMeshComponent>("TileFourMesh");
	TileFour->SetupAttachment(BaseMeshComp);
	Tiles.Add(TileFour);

	TileFive = CreateDefaultSubobject<UStaticMeshComponent>("TileFiveMesh");
	TileFive->SetupAttachment(BaseMeshComp);
	Tiles.Add(TileFive);

	TileSix = CreateDefaultSubobject<UStaticMeshComponent>("TileSixMesh");
	TileSix->SetupAttachment(BaseMeshComp);
	Tiles.Add(TileSix);

	TileSeven = CreateDefaultSubobject<UStaticMeshComponent>("TileSevenMesh");
	TileSeven->SetupAttachment(BaseMeshComp);
	Tiles.Add(TileSeven);

	TileEight = CreateDefaultSubobject<UStaticMeshComponent>("TileEightMesh");
	TileEight->SetupAttachment(BaseMeshComp);
	Tiles.Add(TileEight);

	TileNine = CreateDefaultSubobject<UStaticMeshComponent>("TileNineMesh");
	TileNine->SetupAttachment(BaseMeshComp);
	Tiles.Add(TileNine);

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

	bIsGaming = false;
}

void ATileMiniGame::BeginPlay()
{
	Super::BeginPlay();

	PlayerCharacter = Cast<APCharacter>(GetWorld()->GetGameInstance()->GetFirstLocalPlayerController()->GetPawn());

	HUD = Cast<ARelicHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
}

void ATileMiniGame::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	FKey KeyPressed = EKeys::LeftMouseButton;
	
	
	if (TileInFocus.Num() > 0 && bIsGaming)
	{
		FVector2D MousePosition;

		// IsMouseButton is looking for input from the button itself, not the mouse axis
		if (PlayerController->GetGameInstance()->GetGameViewportClient()->GetMousePosition(MousePosition) && KeyPressed.IsMouseButton())
		{
			FVector TileLocation = TileInFocus[0]->GetComponentLocation();
			TileInFocus[0]->SetWorldLocation(FVector(TileLocation.X, MousePosition.X, TileLocation.Z));

			//check(GEngine != nullptr);

			//FString MousePosString = MousePosition.ToString();
			//UE_LOG(LogTemp, Warning, TEXT(" %s "), *MousePosString); 

			//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Magenta, MousePosString);
		}
	}
}

void ATileMiniGame::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent);
	APController* PlayerBaseController = CastChecked<APController>(Controller);

	// TODO: Break Select & Move tiles into separate actions again, use MouseX & Mouse Y to select, use LMB to drag
	EnhancedInputComponent->BindAction(PlayerBaseController->TileGameAction, ETriggerEvent::Triggered, this, &ATileMiniGame::SelectTile);
	EnhancedInputComponent->BindAction(PlayerBaseController->TileGameAction, ETriggerEvent::Completed, this, &ATileMiniGame::DropTiles);
	EnhancedInputComponent->BindAction(PlayerBaseController->EscapeAction, ETriggerEvent::Completed, this, &ATileMiniGame::OnPuzzleAbandoned);

	ULocalPlayer* LocalPlayer = PlayerBaseController->GetLocalPlayer();

	check(LocalPlayer);
	UEnhancedInputLocalPlayerSubsystem* Subsystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();

	check(Subsystem);
	Subsystem->ClearAllMappings();
	Subsystem->AddMappingContext(PlayerBaseController->PCMappingContext, 0);
}

void ATileMiniGame::SelectTile(const FInputActionValue& Value)
{
	PlayerController = Cast<APController>(this->GetController());
	
	FHitResult HitResult;

	ECollisionChannel CollisionChannel = ECC_Pawn;
	
	if (PlayerController)
	{
		for (int i = 1; i < Tiles.Num(); i++)
		{
			if (PlayerController->GetHitResultUnderCursor(CollisionChannel, false, HitResult))
			{
				if (HitResult.Component == Tiles[i])
				{
					check(GEngine != nullptr);

					FString CompName = HitResult.Component->GetName();
					//UE_LOG(LogTemp, Warning, TEXT(" %s "), *CompName); 

					GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, CompName);

					TileInFocus.Empty();
					TileInFocus.Add(Tiles[i]);
				}
			}
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("ATileGame: Ref to Player Contoller not valid."));
	}
}

void ATileMiniGame::DropTiles(const FInputActionValue& Value)
{
	
}

void ATileMiniGame::OnBecomePossessed()
{
	if (PlayerCharacter)
	{
		bIsGaming = true;
		
		PlayerCharacter->GetController()->Possess(this);
		AutoPossessPlayer = EAutoReceiveInput::Player0;
		PlayerCharacter->SetActorHiddenInGame(true);

		FString CheckController = this->GetController()->GetName();
		UE_LOG(LogTemp, Warning, TEXT(" %s "), *CheckController); 

		PlayerController = Cast<APController>(this->Controller);
		
		if (PlayerController)
		{
			// Not sure if this is still necessary, but it makes me feel safe
			PCMappingContext = {PlayerController->PCMappingContext};
			PlayerController->SetShowMouseCursor(true);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("ATileGame: Ref to Player Contoller not valid."));
		}
		
		UE_LOG(LogTemp, Warning, TEXT("ATileGame: All refs valid. Pawn should be possessed.")); 
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("ATileGame: Ref to Player Character not valid.")); 

	}
}

void ATileMiniGame::OnBecomeUnPossessed()
{
	if (PlayerCharacter)
	{
		bIsGaming = false;
		
		GetController()->UnPossess();
		PlayerCharacter->AutoPossessPlayer = EAutoReceiveInput::Player0;
		PlayerCharacter->SetActorHiddenInGame(false);

		PlayerController = Cast<APController>(GetWorld()->GetGameInstance()->GetPrimaryPlayerController());
		
		if (PlayerController)
		{
			PlayerController->Possess(PlayerCharacter);
			PlayerController->SetShowMouseCursor(false);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("ATileGame: Ref to Player Contoller not valid."));

		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("ATileGame: Ref to Player Character not valid.")); 

	}
}

void ATileMiniGame::OnPuzzleSolved()
{
}

void ATileMiniGame::OnPuzzleAbandoned()
{
	// Something to save the puzzle state here
	
	OnBecomeUnPossessed();
}


