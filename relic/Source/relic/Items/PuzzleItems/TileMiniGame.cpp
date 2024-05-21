#include "TileMiniGame.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "TilePiece.h"
#include "Camera/CameraActor.h"
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
	//CameraComp->SetAutoActivate(true);

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

	TileSelectNum = 1;
}

void ATileMiniGame::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void ATileMiniGame::SelectTile()
{
	if (Triggers.Num() > 0)
	{
		for (int i = 1; i < Triggers.Num(); i++)
		{
			Triggers[i]->SetHiddenInGame(true);
		}
	}

	TriggerOne->SetHiddenInGame(true);
	Actors.Empty();

	bIsGaming = true;
	
	switch (TileSelectNum)
	{
	case 1:
		TriggerOne->SetHiddenInGame(false);
		TriggerOne->ShapeColor = FColor::Red;

		GetOverlappingTiles(TriggerOne);
		
		break;
		
	case 2:
		TriggerTwo->SetHiddenInGame(false);
		TriggerTwo->ShapeColor = FColor::Red;

		GetOverlappingTiles(TriggerTwo);
		
		break;
		
	case 3:
		TriggerThree->SetHiddenInGame(false);
		TriggerThree->ShapeColor = FColor::Red;
		
		GetOverlappingTiles(TriggerThree);
		
		break;
		
	case 4:
		TriggerFour->SetHiddenInGame(false);
		TriggerFour->ShapeColor = FColor::Red;
		
		GetOverlappingTiles(TriggerFour);
		
		break;
		
	case 5:
		TriggerFive->SetHiddenInGame(false);
		TriggerFive->ShapeColor = FColor::Red;
		
		GetOverlappingTiles(TriggerFive);
		
		break;
		
	case 6:
		TriggerSix->SetHiddenInGame(false);
		TriggerSix->ShapeColor = FColor::Red;
		
		GetOverlappingTiles(TriggerSix);
		
		break;
		
	case 7:
		TriggerSeven->SetHiddenInGame(false);
		TriggerSeven->ShapeColor = FColor::Red;
		
		GetOverlappingTiles(TriggerSeven);
		
		break;
		
	case 8:
		TriggerEight->SetHiddenInGame(false);
		TriggerEight->ShapeColor = FColor::Red;
		
		GetOverlappingTiles(TriggerEight);
		
		break;
		
	case 9:
		TriggerNine->SetHiddenInGame(false);
		TriggerNine->ShapeColor = FColor::Red;
		
		GetOverlappingTiles(TriggerNine);
		
		break;
		
	default:
		break;
	}
}

/*
void ATileMiniGame::UpdateSelection()
{
	if (Triggers.Num() > 0)
	{
		for (int i = 1; i < Triggers.Num(); i++)
		{
			if (Triggers[i]->ComponentTags.Contains("TriggerOne") && TileSelectNum == 1 ||
				Triggers[i]->ComponentTags.Contains("TriggerTwo") && TileSelectNum == 2 ||
				Triggers[i]->ComponentTags.Contains("TriggerThree") && TileSelectNum == 3 ||
				Triggers[i]->ComponentTags.Contains("TriggerFour") && TileSelectNum == 4 ||
				Triggers[i]->ComponentTags.Contains("TriggerFive") && TileSelectNum == 5 ||
				Triggers[i]->ComponentTags.Contains("TriggerSix") && TileSelectNum == 6 ||
				Triggers[i]->ComponentTags.Contains("TriggerSeven") && TileSelectNum == 7 ||
				Triggers[i]->ComponentTags.Contains("TriggerEight") && TileSelectNum == 8 ||
				Triggers[i]->ComponentTags.Contains("TriggerNine") && TileSelectNum == 9)
			{}
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("ATileGame: No triggers found.")); 
	}
}*/

void ATileMiniGame::PossessTile(const FInputActionValue& Value)
{
	if (bIsGaming)
	{
		if (TilePiece)
		{
			OnBecomeUnPossessed();
			TilePiece->OnBecomePossessed();
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("ATileGame: Can't posess tile. No valid ref to ATilePiece."));
		}
	}
}

void ATileMiniGame::MoveSelectionUp(const FInputActionValue& Value)
{
	if (TileSelectNum > 3)
	{
		TileSelectNum -= 3;
		SelectTile();
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("ATileGame: Can't move up."));
	}
}

void ATileMiniGame::MoveSelectionDown(const FInputActionValue& Value)
{
	if (TileSelectNum <= 6)
	{
		TileSelectNum += 3;
		SelectTile();
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("ATileGame: Can't move down."));
	}
}

void ATileMiniGame::MoveSelectionLeft(const FInputActionValue& Value)
{
	if (TileSelectNum > 1)
	{
		TileSelectNum--;
		SelectTile();
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("ATileGame: Can't move right."));
	}
}

void ATileMiniGame::MoveSelectionRight(const FInputActionValue& Value)
{
	if (TileSelectNum < 9)
	{
		TileSelectNum++;
		SelectTile();
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("ATileGame: Can't move left."));
	}
}

void ATileMiniGame::OnBecomePossessed()
{
	if (PlayerCharacter)
	{
		PlayerCharacter->GetController()->Possess(this);
		AutoPossessPlayer = EAutoReceiveInput::Player0;
		PlayerCharacter->SetActorHiddenInGame(true);

		//TODO: figure out how to make camera view change to this pawns camera consistently

		FString CheckController = this->GetController()->GetName();
		UE_LOG(LogTemp, Warning, TEXT(" %s "), *CheckController); 

		PlayerController = Cast<APController>(this->Controller);
		
		if (PlayerController)
		{
			// Not sure if this is still necessary, but it makes me feel safe
			PCMappingContext = {PlayerController->PCMappingContext};
			PlayerController->SetViewTarget(TileFacingCamera);
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

	//SelectTile();

	// Currently crashes game:
	//CheckTilePlacement();
}

void ATileMiniGame::OnBecomeUnPossessed()
{
	if (PlayerCharacter)
	{
		GetController()->UnPossess();
		PlayerCharacter->AutoPossessPlayer = EAutoReceiveInput::Player0;
		PlayerCharacter->SetActorHiddenInGame(false);

		PlayerController = Cast<APController>(GetWorld()->GetGameInstance()->GetPrimaryPlayerController());
		
		if (PlayerController)
		{
			PlayerController->Possess(PlayerCharacter);
			//PlayerController->SetShowMouseCursor(false);

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

	bIsGaming = false;
}


void ATileMiniGame::CheckTilePlacement()
{
	if (Triggers.Num() > 0)
	{
		for (int i = 1; i < Triggers.Num(); i++)
		{
			Triggers[i]->GetOverlappingComponents(OverlappingTiles);

			for (int n = 1; n < OverlappingTiles.Num(); n++)
			{
				if (OverlappingTiles[n]->ComponentTags.Num() > 0)
				{
					FName OverlapTag = OverlappingTiles[n]->ComponentTags[0];
					//UE_LOG(LogTemp, Warning, TEXT("ATileGame, TriggerOne: Adjacent tiles present - %s ."), *NeighborTag.ToString());

					if (Triggers[i]->ComponentTags.Contains("TriggerOne") && OverlapTag == "TileOne" ||
						Triggers[i]->ComponentTags.Contains("TriggerTwo") && OverlapTag == "TileTwo" ||
						Triggers[i]->ComponentTags.Contains("TriggerThree") && OverlapTag == "TileThree" ||
						Triggers[i]->ComponentTags.Contains("TriggerFour") && OverlapTag == "TileFour" ||
						Triggers[i]->ComponentTags.Contains("TriggerFive") && OverlapTag == "TileFive" ||
						Triggers[i]->ComponentTags.Contains("TriggerSix") && OverlapTag == "TileSix" ||
						Triggers[i]->ComponentTags.Contains("TriggerSeven") && OverlapTag == "TileSeven" ||
						Triggers[i]->ComponentTags.Contains("TriggerEight") && OverlapTag == "TileEight" ||
						Triggers[i]->ComponentTags.Contains("TriggerNine") && OverlapTag == "TileNine")
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

void ATileMiniGame::GetOverlappingTiles(UPrimitiveComponent* Trigger)
{
	Trigger->GetOverlappingActors(Actors);

	FString CompName = Trigger->GetName();
		
	for (int o = 1; o < Actors.Num(); o++)
	{
		if (Actors[o]->GetClass() != this->GetClass())
		{
			TilePiece = Cast<ATilePiece>(Actors[o]);

			if (TilePiece)
			{
				UE_LOG(LogTemp, Warning, TEXT("ATileGame: %s , ATilePiece cast succeeded!."), *CompName);
				TilePiece->HighlightTile();
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("ATileGame: %s , ATilePiece cast failed."), *CompName);
			}
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("ATileGame: %s , ATilePiece no matching actors of class found."), *CompName);
		}
	}
}


void ATileMiniGame::OnPuzzleAbandoned()
{
	//TODO: Something to save the puzzle state here

	if (Triggers.Num() > 0)
	{
		for (int i = 1; i < Triggers.Num(); i++)
		{
			Triggers[i]->SetHiddenInGame(true);
		}
	}

	TriggerOne->SetHiddenInGame(true);
	
	OnBecomeUnPossessed();
}


void ATileMiniGame::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent);
	APController* PlayerBaseController = CastChecked<APController>(Controller);
	
	EnhancedInputComponent->BindAction(PlayerBaseController->TileSelectAction, ETriggerEvent::Triggered, this, &ATileMiniGame::PossessTile);
	EnhancedInputComponent->BindAction(PlayerBaseController->EscapeAction, ETriggerEvent::Completed, this, &ATileMiniGame::OnPuzzleAbandoned);

	EnhancedInputComponent->BindAction(PlayerBaseController->SelectUpAction, ETriggerEvent::Completed, this, &ATileMiniGame::MoveSelectionUp);
	EnhancedInputComponent->BindAction(PlayerBaseController->SelectDownAction, ETriggerEvent::Completed, this, &ATileMiniGame::MoveSelectionDown);
	EnhancedInputComponent->BindAction(PlayerBaseController->SelectLeftAction, ETriggerEvent::Completed, this, &ATileMiniGame::MoveSelectionLeft);
	EnhancedInputComponent->BindAction(PlayerBaseController->SelectRightAction, ETriggerEvent::Completed, this, &ATileMiniGame::MoveSelectionRight);
	
	ULocalPlayer* LocalPlayer = PlayerBaseController->GetLocalPlayer();

	check(LocalPlayer);
	UEnhancedInputLocalPlayerSubsystem* Subsystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();

	check(Subsystem);
	Subsystem->ClearAllMappings();
	Subsystem->AddMappingContext(PlayerBaseController->PCMappingContext, 0);
}