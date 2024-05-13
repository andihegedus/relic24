#include "TilePiece.h"

#include "Components/SphereComponent.h"
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

void ATilePiece::OnBecomePossessed()
{
	if (PlayerCharacter)
	{
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
			//PlayerController->SetShowMouseCursor(true);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("ATilePiece: Ref to Player Contoller not valid."));
		}
		
		UE_LOG(LogTemp, Warning, TEXT("ATilePiece: All refs valid. Pawn should be possessed."));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("ATilePiece: Ref to Player Character not valid.")); 

	}
}

void ATilePiece::OnBecomeUnPossessed()
{
	if (PlayerCharacter)
	{
		GetController()->UnPossess();
		//PlayerCharacter->AutoPossessPlayer = EAutoReceiveInput::Player0;
		//PlayerCharacter->SetActorHiddenInGame(false);

		PlayerController = Cast<APController>(GetWorld()->GetGameInstance()->GetPrimaryPlayerController());
		
		if (PlayerController)
		{
			//PlayerController->Possess(PlayerCharacter);
			//PlayerController->SetShowMouseCursor(false);

			/*if (bSolvedTilePuzzle)
			{
				PlayerCharacter->OnTilePuzzleSolved.Broadcast();
			}*/
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("ATilePiece: Ref to Player Contoller not valid."));

		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("ATilePiece: Ref to Player Character not valid.")); 

	}
}

void ATilePiece::BeginPlay()
{
	Super::BeginPlay();

	PlayerCharacter = Cast<APCharacter>(GetWorld()->GetGameInstance()->GetFirstLocalPlayerController()->GetPawn());

	HUD = Cast<ARelicHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());

	FindAdjacentTile();
}

void ATilePiece::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	//TODO: move this to contingent on bool from TileMiniGame start
	//FindAdjacentTile();
}

void ATilePiece::FindAdjacentTile()
{
	//SphereCollision->GetOverlappingComponents(Neighbors);

	this->GetOverlappingComponents(Neighbors);

	this->GetOverlappingActors(Actors);
	
	for (int i = 1; i < Neighbors.Num(); i++)
	{
		if (Neighbors[i]->ComponentTags.Num() > 0)
		{
			FName NeighborTag = Neighbors[i]->ComponentTags[0];
			UE_LOG(LogTemp, Warning, TEXT("ATilePiece: I am the tile neighbor, %s."), *NeighborTag.ToString());
			
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("ATilePiece: No component tags found.")); 
		}
	}
	if (Neighbors.Num() == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("ATilePiece: No neighbors found.")); 
	}
}
