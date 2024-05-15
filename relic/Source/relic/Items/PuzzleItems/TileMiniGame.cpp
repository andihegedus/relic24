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

	TileSelectNum = 1;
	
	// true for testing, until functionality is complete
	//bSolvedTilePuzzle = true;
}

void ATileMiniGame::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

//TODO: This needs to be edited to only move on the Z and Y axes
void ATileMiniGame::SelectTile(const FInputActionValue& Value)
{
	FVector Input = Value.Get<FInputActionValue::Axis3D>();

	const FRotator Rotation = Controller->GetControlRotation();
	const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	AddMovementInput(ForwardDirection, Input.Y);

	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	AddMovementInput(RightDirection, Input.X);
}

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
}

void ATileMiniGame::PossessTile(const FInputActionValue& Value)
{
	
}

void ATileMiniGame::MoveSelectionUp(const FInputActionValue& Value)
{
	if (TileSelectNum > 3)
	{
		TileSelectNum -= 3;
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
	
	CheckTilePlacement();
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
	
	EnhancedInputComponent->BindAction(PlayerBaseController->InteractAction, ETriggerEvent::Triggered, this, &ATileMiniGame::PossessTile);
	EnhancedInputComponent->BindAction(PlayerBaseController->EscapeAction, ETriggerEvent::Completed, this, &ATileMiniGame::OnPuzzleAbandoned);
	EnhancedInputComponent->BindAction(PlayerBaseController->MoveAction, ETriggerEvent::Completed, this, &ATileMiniGame::SelectTile);
	
	ULocalPlayer* LocalPlayer = PlayerBaseController->GetLocalPlayer();

	check(LocalPlayer);
	UEnhancedInputLocalPlayerSubsystem* Subsystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();

	check(Subsystem);
	Subsystem->ClearAllMappings();
	Subsystem->AddMappingContext(PlayerBaseController->PCMappingContext, 0);
}