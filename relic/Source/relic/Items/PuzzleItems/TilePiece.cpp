#include "TilePiece.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "TileMiniGame.h"
#include "Camera/CameraActor.h"
#include "Components/SphereComponent.h"
#include "Engine/LocalPlayer.h"
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
}

void ATilePiece::BeginPlay()
{
	Super::BeginPlay();

	PlayerCharacter = Cast<APCharacter>(GetWorld()->GetGameInstance()->GetFirstLocalPlayerController()->GetPawn());

	HUD = Cast<ARelicHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
}

void ATilePiece::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
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
			UE_LOG(LogTemp, Warning, TEXT("ATileGame: Ref to Player Contoller not valid."));
		}
		
		UE_LOG(LogTemp, Warning, TEXT("ATileGame: All refs valid. Pawn should be possessed."));
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
	FVector Input = Value.Get<FInputActionValue::Axis3D>();

	FVector CurrentTileLocation = this->GetActorLocation();

	float TravelRate = 50.0f;

	FVector NewTileLocation = FVector(CurrentTileLocation.X, CurrentTileLocation.Y, CurrentTileLocation.Z - TravelRate * Input.Z);

	SetActorLocation(NewTileLocation);
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
	EnhancedInputComponent->BindAction(PlayerBaseController->BackAction, ETriggerEvent::Completed, this, &ATilePiece::OnBecomeUnPossessed);
	
	ULocalPlayer* LocalPlayer = PlayerBaseController->GetLocalPlayer();

	check(LocalPlayer);
	UEnhancedInputLocalPlayerSubsystem* Subsystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();

	check(Subsystem);
	Subsystem->ClearAllMappings();
	Subsystem->AddMappingContext(PlayerBaseController->PCMappingContext, 0);
}


