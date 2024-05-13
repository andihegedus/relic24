#include "TileMiniGame.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "TilePiece.h"
#include "Camera/CameraComponent.h"
#include "Components/BoxComponent.h"
#include "Components/SphereComponent.h"
#include "Engine/LocalPlayer.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "relic/PlayerCharacter/PCharacter.h"
#include "relic/PlayerCharacter/PController.h"
#include "relic/System/RelicHUD.h"

ATileMiniGame::ATileMiniGame()
{
	BoxCollision = CreateDefaultSubobject<UBoxComponent>("BoxCollision");
	SetRootComponent(BoxCollision);
	
	TileHolder = CreateDefaultSubobject<UStaticMeshComponent>("TileHolder");
	TileHolder->SetupAttachment(BoxCollision);

	// TODO: There's probably a better, less complicated way to do this
	TriggerOne = CreateDefaultSubobject<USphereComponent>("TriggerOne");
	TriggerOne->SetupAttachment(BoxCollision);
	TriggerOne->ComponentTags.Add("TriggerOne");
	Triggers.Add(TriggerOne);

	TriggerTwo = CreateDefaultSubobject<USphereComponent>("TriggerTwo");
	TriggerTwo->SetupAttachment(BoxCollision);
	TriggerTwo->ComponentTags.Add("TriggerTwo");
	Triggers.Add(TriggerTwo);

	TriggerThree = CreateDefaultSubobject<USphereComponent>("TriggerThree");
	TriggerThree->SetupAttachment(BoxCollision);
	TriggerThree->ComponentTags.Add("TriggerThree");
	Triggers.Add(TriggerThree);

	TriggerFour = CreateDefaultSubobject<USphereComponent>("TriggerFour");
	TriggerFour->SetupAttachment(BoxCollision);
	TriggerFour->ComponentTags.Add("TriggerFour");
	Triggers.Add(TriggerFour);

	TriggerFive = CreateDefaultSubobject<USphereComponent>("TriggerFive");
	TriggerFive->SetupAttachment(BoxCollision);
	TriggerFive->ComponentTags.Add("TriggerFive");
	Triggers.Add(TriggerFive);

	TriggerSix = CreateDefaultSubobject<USphereComponent>("TriggerSix");
	TriggerSix->SetupAttachment(BoxCollision);
	TriggerSix->ComponentTags.Add("TriggerSix");
	Triggers.Add(TriggerSix);

	TriggerSeven = CreateDefaultSubobject<USphereComponent>("TriggerSeven");
	TriggerSeven->SetupAttachment(BoxCollision);
	TriggerSeven->ComponentTags.Add("TriggerSeven");
	Triggers.Add(TriggerSeven);

	TriggerEight = CreateDefaultSubobject<USphereComponent>("TriggerEight");
	TriggerEight->SetupAttachment(BoxCollision);
	TriggerEight->ComponentTags.Add("TriggerEight");
	Triggers.Add(TriggerEight);

	TriggerNine = CreateDefaultSubobject<USphereComponent>("TriggerNine");
	TriggerNine->SetupAttachment(BoxCollision);
	TriggerNine->ComponentTags.Add("TriggerNine");
	Triggers.Add(TriggerNine);

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

	SelectTile();
	
	// true for testing, until functionality is complete
	//bSolvedTilePuzzle = true;
}

void ATileMiniGame::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	/*FKey KeyPressed = EKeys::LeftMouseButton;
	
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
	}*/
}

void ATileMiniGame::SelectTile()
{
	PlayerController = Cast<APController>(this->GetController());

	if (Triggers.Num() > 0)
	{
		for (int i = 1; i < Triggers.Num(); i++)
		{
			Triggers[i]->GetOverlappingComponents(AllTiles);

			if (AllTiles.Num() > 0)
			{
				TilePiece = Cast<ATilePiece>(AllTiles[0]->GetOwner());

				FName TileTag = AllTiles[0]->ComponentTags[0];

				if (TilePiece)
				{
					//TilePiece->OnBecomePossessed();
					UE_LOG(LogTemp, Warning, TEXT("ATileGame: Tile %s found. Tile possessed."), *TileTag.ToString() ); 
				}
				else
				{
					UE_LOG(LogTemp, Warning, TEXT("ATileGame: Cast not valid. Can't possess tile.")); 
				}
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("ATileGame: No tiles found.")); 
			}
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("ATileGame, BeginPlay: No triggers found.")); 
	}
	
}

void ATileMiniGame::DragTiles(const FInputActionValue& Value)
{
}

void ATileMiniGame::DropTiles(const FInputActionValue& Value)
{
	CheckTilePlacement();
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

			/*if (bSolvedTilePuzzle)
			{
				PlayerCharacter->OnTilePuzzleSolved.Broadcast();
			}*/
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

	//OnPuzzleSolved();
}


void ATileMiniGame::CheckTilePlacement()
{
	if (Triggers.Num() > 0)
	{
		for (int i = 1; i < Triggers.Num(); i++)
		{
			Triggers[i]->GetOverlappingComponents(OverlappingTiles);

			if (OverlappingTiles.Num() > 0)
			{
				for (int n = 1; n < OverlappingTiles.Num(); n++)
				{
					if (OverlappingTiles[n]->ComponentTags.Num() > 0)
					{
						FName NeighborTag = OverlappingTiles[n]->ComponentTags[0];
						//UE_LOG(LogTemp, Warning, TEXT("ATileGame, TriggerOne: Adjacent tiles present - %s ."), *NeighborTag.ToString());

						if (Triggers[i]->ComponentTags.Contains("TriggerOne") && NeighborTag == "One" ||
							Triggers[i]->ComponentTags.Contains("TriggerTwo") && NeighborTag == "Two" ||
							Triggers[i]->ComponentTags.Contains("TriggerThree") && NeighborTag == "Three" ||
							Triggers[i]->ComponentTags.Contains("TriggerFour") && NeighborTag == "Four" ||
							Triggers[i]->ComponentTags.Contains("TriggerFive") && NeighborTag == "Five" ||
							Triggers[i]->ComponentTags.Contains("TriggerSix") && NeighborTag == "Six" ||
							Triggers[i]->ComponentTags.Contains("TriggerSeven") && NeighborTag == "Seven" ||
							Triggers[i]->ComponentTags.Contains("TriggerEight") && NeighborTag == "Eight" ||
							Triggers[i]->ComponentTags.Contains("TriggerNine") && NeighborTag == "Nine")
						{
							SolutionCount++;
						}
					}
					else
					{
						UE_LOG(LogTemp, Warning, TEXT("ATileGame: Number identifier tag not found.")); 
					}
				}
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("ATileGame: No adjacent tiles found.")); 
			}
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("ATileGame: No triggers found.")); 
	}

	if (SolutionCount == 9)
	{
		OnPuzzleSolved();
		OnBecomeUnPossessed();
	}
	else if (SolutionCount < 9)
	{
		SolutionCount = 0;
		OverlappingTiles.Empty();
	}
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