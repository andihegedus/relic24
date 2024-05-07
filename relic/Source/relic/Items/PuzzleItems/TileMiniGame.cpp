#include "TileMiniGame.h"

#include <string>

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "TilePiece.h"
#include "Camera/CameraComponent.h"
#include "Components/BoxComponent.h"
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
	BoxCollision = CreateDefaultSubobject<UBoxComponent>("BoxCollision");
	SetRootComponent(BoxCollision);
	
	TileHolder = CreateDefaultSubobject<UStaticMeshComponent>("TileHolder");
	TileHolder->SetupAttachment(BoxCollision);

	// TODO: There's probably a cleaner way to do this
	/*TilePiece = CreateDefaultSubobject<ATilePiece>("TilePieceOne");
	Pieces.Add(TilePiece);

	TileTwo = CreateDefaultSubobject<UStaticMeshComponent>("TileTwoMesh");;
	Tiles.Add(TileTwo);

	TileThree = CreateDefaultSubobject<UStaticMeshComponent>("TileThreeMesh");
	Tiles.Add(TileThree);

	TileFour = CreateDefaultSubobject<UStaticMeshComponent>("TileFourMesh");
	Tiles.Add(TileFour);

	TileFive = CreateDefaultSubobject<UStaticMeshComponent>("TileFiveMesh");
	Tiles.Add(TileFive);

	TileSix = CreateDefaultSubobject<UStaticMeshComponent>("TileSixMesh");
	Tiles.Add(TileSix);

	TileSeven = CreateDefaultSubobject<UStaticMeshComponent>("TileSevenMesh");
	Tiles.Add(TileSeven);

	TileEight = CreateDefaultSubobject<UStaticMeshComponent>("TileEightMesh");
	Tiles.Add(TileEight);

	TileNine = CreateDefaultSubobject<UStaticMeshComponent>("TileNineMesh");
	Tiles.Add(TileNine);

	for (int i = 0; i < Tiles.Num(); i++)
	{
		Tiles[i]->SetupAttachment(BoxCollision);
	}

	TileMovement = CreateDefaultSubobject<UFloatingPawnMovement>("MovementComp");*/

	// Setup PC Camera components
	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArmComp->SetupAttachment(GetRootComponent());
	
	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComp->SetupAttachment(SpringArmComp, USpringArmComponent::SocketName);

	// Assign SpringArm class variables
	SpringArmComp->TargetArmLength = 300.f;

	MiniGameTag = "TileGame";
	BoxCollision->ComponentTags.Add(MiniGameTag);
	this->Tags.Add(MiniGameTag);

	bIsGaming = false;
	bIsSelected = false;
}

void ATileMiniGame::BeginPlay()
{
	Super::BeginPlay();

	PlayerCharacter = Cast<APCharacter>(GetWorld()->GetGameInstance()->GetFirstLocalPlayerController()->GetPawn());

	HUD = Cast<ARelicHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());

	// true for testing, until functionality is complete
	bSolvedTilePuzzle = true;
}

void ATileMiniGame::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	FKey KeyPressed = EKeys::LeftMouseButton;
	
	if (TileInFocus.Num() > 0 && bIsGaming && bIsSelected)
	{
		FVector2D MousePosition;

		// IsMouseButton is looking for input from the button itself, not the mouse axis
		if (PlayerController->GetGameInstance()->GetGameViewportClient()->GetMousePosition(MousePosition)) // && KeyPressed.IsMouseButton()
		{
			FVector TileLocation = TileInFocus[0]->GetComponentLocation();

			// There has to be a better way to convert 2D space to 3D world space, but I haven't found it yet - I don't recommend the method below
			TileInFocus[0]->SetRelativeLocation(FVector(TileLocation.X + 3535, -MousePosition.X + 755, -MousePosition.Y + 250));

			//check(GEngine != nullptr);

			//FString MousePosString = MousePosition.ToString();
			//UE_LOG(LogTemp, Warning, TEXT(" %s "), *MousePosString); 

			//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Magenta, MousePosString);
		}
	}
}

void ATileMiniGame::SelectTile(const FInputActionValue& Value)
{
	PlayerController = Cast<APController>(this->GetController());
	
	FHitResult HitResult;

	//const FKey KeyPressed = EKeys::LeftMouseButton;
	//int KeyPressedValue = GetInputAxisKeyValue(KeyPressed);

	ECollisionChannel CollisionChannel = ECC_Pawn;
	
	if (PlayerController)
	{
		for (int i = 1; i < Tiles.Num(); i++)
		{
			if (PlayerController->GetHitResultUnderCursor(CollisionChannel, false, HitResult) && Value.IsNonZero()) // && (KeyPressedValue == 1)
			{
				if (HitResult.Component == Tiles[i])
				{
					bIsSelected = true;
					
					check(GEngine != nullptr);

					FString CompName = HitResult.Component->GetName();
					//UE_LOG(LogTemp, Warning, TEXT(" %s "), *CompName); 

					GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, CompName);

					TileInFocus.Empty();
					TileInFocus.Add(Tiles[i]);
				}
			}
			else
			{
				bIsSelected = false;
				TileInFocus.Empty();
				return;
			}
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("ATileGame: Ref to Player Contoller not valid."));
	}
}

void ATileMiniGame::DragTiles(const FInputActionValue& Value)
{
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

			if (bSolvedTilePuzzle)
			{
				PlayerCharacter->OnTilePuzzleSolved.Broadcast();
			}
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

	OnPuzzleSolved();
}

void ATileMiniGame::OnPuzzleSolved()
{
	if (PlayerCharacter)
	{
		PlayerCharacter->TilePuzzleSolved();
	}
}

void ATileMiniGame::OnPuzzleAbandoned()
{
	// Something to save the puzzle state here
	
	OnBecomeUnPossessed();
}


void ATileMiniGame::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent);
	APController* PlayerBaseController = CastChecked<APController>(Controller);

	// TODO: Break Select & Move tiles into separate actions again, use MouseX & Mouse Y to select, use LMB to drag
	EnhancedInputComponent->BindAction(PlayerBaseController->TileGameAction, ETriggerEvent::Triggered, this, &ATileMiniGame::SelectTile);
	EnhancedInputComponent->BindAction(PlayerBaseController->TileGameAction, ETriggerEvent::Ongoing, this, &ATileMiniGame::DragTiles);
	EnhancedInputComponent->BindAction(PlayerBaseController->TileGameAction, ETriggerEvent::Canceled, this, &ATileMiniGame::DropTiles);
	EnhancedInputComponent->BindAction(PlayerBaseController->EscapeAction, ETriggerEvent::Completed, this, &ATileMiniGame::OnPuzzleAbandoned);

	ULocalPlayer* LocalPlayer = PlayerBaseController->GetLocalPlayer();

	check(LocalPlayer);
	UEnhancedInputLocalPlayerSubsystem* Subsystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();

	check(Subsystem);
	Subsystem->ClearAllMappings();
	Subsystem->AddMappingContext(PlayerBaseController->PCMappingContext, 0);
}