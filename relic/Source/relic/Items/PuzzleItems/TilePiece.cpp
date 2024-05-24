#include "TilePiece.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "TileMiniGame.h"
#include "Camera/CameraActor.h"
#include "Components/SphereComponent.h"
#include "Engine/LocalPlayer.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "GameFramework/PlayerController.h"
#include "relic/PlayerCharacter/PCharacter.h"
#include "relic/PlayerCharacter/PController.h"
#include "relic/System/RelicHUD.h"

ATilePiece::ATilePiece()
{
	TilePieceComp = CreateDefaultSubobject<UStaticMeshComponent>("InstancedMesh");
	SetRootComponent(TilePieceComp);

	SphereCollision = CreateDefaultSubobject<USphereComponent>("CollisionTop");
	SphereCollision->SetupAttachment(TilePieceComp);

	FloatingPawnMovement = CreateDefaultSubobject<UFloatingPawnMovement>("PawnMovement");
	
	// Untick inherit R,P,Y for character
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	CheckInteractionDistance = 5.f;
}

void ATilePiece::BeginPlay()
{
	Super::BeginPlay();

	PlayerCharacter = Cast<APCharacter>(GetWorld()->GetGameInstance()->GetFirstLocalPlayerController()->GetPawn());

	HUD = Cast<ARelicHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());

	bStopMovement = false;

	//this->SetActorLocation(OGLocation);
}

void ATilePiece::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (bStopMovement == true)
	{
		this->bLockLocation = true;
	}
	else
	{
		this->bLockLocation = false;
	}
}

void ATilePiece::OnBecomePossessed()
{
	/*this->GetOverlappingComponents(Neighbors);
	
	for (int i = 1; i < Neighbors.Num(); i++)
	{
		if (Neighbors[i]->GetAttachmentRootActor()->GetClass() != this->GetClass())
		{
			TileMiniGame = Cast<ATileMiniGame>(Neighbors[i]->GetAttachmentRootActor());
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("ATilePiece: Cast to ATileGame failed.")); 
		}
	}
	
	if (TileMiniGame)
	{
		TileMiniGame->GetController()->Possess(this);

		AutoPossessPlayer = EAutoReceiveInput::Player0;

		FString CheckController = this->GetController()->GetName();
		UE_LOG(LogTemp, Warning, TEXT(" %s "), *CheckController);

		PlayerController = Cast<APController>(this->Controller);

		if (PlayerController)
		{
			// Not sure if this is still necessary, but it makes me feel safe
			PCMappingContext = {PlayerController->PCMappingContext};
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("ATilePiece: Ref to Player Contoller not valid."));
		}
	
		UE_LOG(LogTemp, Warning, TEXT("ATilePiece: All refs valid. Pawn should be possessed."));
	}*/
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
			UE_LOG(LogTemp, Warning, TEXT("ATilePiece: Ref to Player Contoller not valid."));
		}

		if (TilePieceComp->ComponentTags.Num() > 0)
		{
			FName Tag = TilePieceComp->ComponentTags[0];
		
			UE_LOG(LogTemp, Warning, TEXT("ATilePiece: All refs valid. Pawn %s should be possessed."), *Tag.ToString());
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("ATilePiece: Ref to ATileGame not valid.")); 
	}

	//UE_LOG(LogTemp, Warning, TEXT("ATilePiece: Possession action firing!")); 
}

void ATilePiece::OnBecomeUnPossessed()
{
	if (PlayerCharacter)
	{
		//GetController()->UnPossess();
		//PlayerCharacter->TileGame->OnBecomePossessed();

		UE_LOG(LogTemp, Warning, TEXT("ATilePiece: OnBecomeUnpossessed action triggered successfully.")); 
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("ATilePiece: Ref to Player Character not valid.")); 
	}
}

//TODO: This needs to be edited to only move on the Z and Y axes
void ATilePiece::MoveTileDown(const FInputActionValue& Value)
{
	bStopMovement = false;
	
	this->GetOverlappingActors(Actors);
	
	for (int i = 1; i < Actors.Num(); i++)
	{
		if (Actors[i]->GetClass() == this->GetClass())
		{
			bStopMovement = true;

			return;
		}
	}
	
	FVector CurrentLocation = this->GetActorLocation();

	const FVector Move = FVector(CurrentLocation.X, CurrentLocation.Y, CurrentLocation.Z - 1.f);
	SetActorLocation(Move);
	
	//UE_LOG(LogTemp, Warning, TEXT("ATilePiece: Moving Down!, %s "), *Move.ToString());
	//UE_LOG(LogTemp, Warning, TEXT("ATilePiece: Moving left/right!, %s "), *RightDirection.ToString()); 
}

void ATilePiece::MoveTileUp(const FInputActionValue& Value)
{
	bStopMovement = false;
	
	this->GetOverlappingActors(Actors);
	
	for (int i = 1; i < Actors.Num(); i++)
	{
		if (Actors[i]->GetClass() == this->GetClass())
		{
			bStopMovement = true;

			return;
		}
	}
	
	FVector CurrentLocation = this->GetActorLocation();

	const FVector Move = FVector(CurrentLocation.X, CurrentLocation.Y, CurrentLocation.Z + 1.f);
	SetActorLocation(Move);
}

void ATilePiece::MoveTileRight(const FInputActionValue& Value)
{
	bStopMovement = false;
	
	this->GetOverlappingActors(Actors);
	
	for (int i = 1; i < Actors.Num(); i++)
	{
		if (Actors[i]->GetClass() == this->GetClass())
		{
			/*FVector CurrentLocation = this->GetActorLocation();
			
			FMath::Clamp(Stop, CurrentLocation.Y, CurrentLocation.Y);

			FVector StoppedLocation = FVector(CurrentLocation.X, Stop, CurrentLocation.Z);

			SetActorLocation(StoppedLocation);*/

			bStopMovement = true;

			return;
		}
	}
	
	FVector CurrentLocation = this->GetActorLocation();

	const FVector Move = FVector(CurrentLocation.X, CurrentLocation.Y - 1.f, CurrentLocation.Z);
	SetActorLocation(Move);
}

void ATilePiece::MoveTileLeft(const FInputActionValue& Value)
{
	InteractionInfo.CheckLastInteractionTime = GetWorld()->GetTimeSeconds();

	FVector CurrentLocation = GetActorLocation();
	
	LineTraceStart = FVector(CurrentLocation.X, CurrentLocation.Y + 115.f, CurrentLocation.Z + 55.f);
	
	FVector LineTraceEnd{FVector(LineTraceStart.X, LineTraceStart.Y - CheckInteractionDistance, LineTraceStart.Z)};
	float LookDirection = FVector::DotProduct(GetActorForwardVector(), GetViewRotation().Vector());

	if (LookDirection > 0)
	{
		// Visualize our trace hit line
		DrawDebugLine(GetWorld(), LineTraceEnd, LineTraceStart, FColor::Magenta, false, 1.0f, 0, 50.f);

		// Contains useful things for line tracing
		FCollisionQueryParams QueryParams;

		// I'm the class shooting out the line trace, don't want to hit myself
		QueryParams.AddIgnoredActor(this);

		// Store the result of the line trace, also contains the actor that was hit
		FHitResult TraceHit;

		if(GetWorld()->LineTraceSingleByChannel(TraceHit, LineTraceEnd, LineTraceStart, ECC_Visibility, QueryParams))
		{
			if (TraceHit.GetActor()->GetClass() == this->GetClass())
			{
				bStopMovement = true;

				return;
			}
		}
	}
	
	/*bStopMovement = false;
	
	this->GetOverlappingActors(Actors);
	
	for (int i = 1; i < Actors.Num(); i++)
	{
		if (Actors[i]->GetClass() == this->GetClass())
		{
			FVector CurrentLocation = this->GetActorLocation();
			
			FMath::Clamp(Stop, CurrentLocation.Y - 50.f, CurrentLocation.Y);

			FVector StoppedLocation = FVector(CurrentLocation.X, Stop, CurrentLocation.Z);

			SetActorLocation(StoppedLocation);

			bStopMovement = true;

			return;
		}
	}*/
	
	//FVector CurrentLocation = this->GetActorLocation();

	const FVector Move = FVector(CurrentLocation.X, CurrentLocation.Y + 1.f, CurrentLocation.Z);
	SetActorLocation(Move);
}

//TODO: Learn more about overlay materials, make these translucent instead of opaque - they are completely hiding the tiles
void ATilePiece::HighlightTile()
{
	TilePieceComp->SetOverlayMaterial(HighlightMaterial);
}

void ATilePiece::HideHighlight()
{
	TilePieceComp->SetOverlayMaterial(TransparentMaterial);
}

void ATilePiece::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent);
	APController* PlayerBaseController = CastChecked<APController>(Controller);
	
	EnhancedInputComponent->BindAction(PlayerBaseController->TileDownAction, ETriggerEvent::Triggered, this, &ATilePiece::MoveTileDown);
	EnhancedInputComponent->BindAction(PlayerBaseController->TileUpAction, ETriggerEvent::Triggered, this, &ATilePiece::MoveTileUp);
	EnhancedInputComponent->BindAction(PlayerBaseController->TileRightAction, ETriggerEvent::Triggered, this, &ATilePiece::MoveTileRight);
	EnhancedInputComponent->BindAction(PlayerBaseController->TileLeftAction, ETriggerEvent::Triggered, this, &ATilePiece::MoveTileLeft);
	EnhancedInputComponent->BindAction(PlayerBaseController->BackAction, ETriggerEvent::Completed, this, &ATilePiece::OnBecomeUnPossessed);
	
	ULocalPlayer* LocalPlayer = PlayerBaseController->GetLocalPlayer();

	check(LocalPlayer);
	UEnhancedInputLocalPlayerSubsystem* Subsystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();

	check(Subsystem);
	Subsystem->ClearAllMappings();
	Subsystem->AddMappingContext(PlayerBaseController->PCMappingContext, 0);
}


