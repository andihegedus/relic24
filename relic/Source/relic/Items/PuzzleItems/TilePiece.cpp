#include "TilePiece.h"

#include "Components/SphereComponent.h"

ATilePiece::ATilePiece()
{
	TilePieceComp = CreateDefaultSubobject<UStaticMeshComponent>("InstancedMesh");
	SetRootComponent(TilePieceComp);

	SphereCollisionTop = CreateDefaultSubobject<USphereComponent>("CollisionTop");
	SphereCollisionTop->SetupAttachment(TilePieceComp);

	SphereCollisionBottom = CreateDefaultSubobject<USphereComponent>("CollisionBottom");
	SphereCollisionBottom->SetupAttachment(TilePieceComp);

	SphereCollisionLeft = CreateDefaultSubobject<USphereComponent>("CollisionLeft");
	SphereCollisionLeft->SetupAttachment(TilePieceComp);

	SphereCollisionRight = CreateDefaultSubobject<USphereComponent>("CollisionRight");
	SphereCollisionRight->SetupAttachment(TilePieceComp);

	//TilePieceTag = "TilePiece";
	//TilePieceComp->ComponentTags.Add(TilePieceTag);
	//this->Tags.Add(TilePieceTag);

	//FindAdjacentTile();
}

void ATilePiece::BeginPlay()
{
	Super::BeginPlay();

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
	SphereCollisionTop->GetOverlappingComponents(Pieces);

	if (Pieces.Num() > 0)
	{
		for (int i = 1; i < Pieces.Num(); i++)
		{
			if (Pieces[i]->ComponentTags.Num() > 0)
			{
				FName NeighborTag = Pieces[i]->ComponentTags[0];
				UE_LOG(LogTemp, Warning, TEXT("%s"), *NeighborTag.ToString());
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("ATilePiece: Number identifier tag not found.")); 
			}
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("ATilePiece: No adjacent tiles found.")); 
	}
}
