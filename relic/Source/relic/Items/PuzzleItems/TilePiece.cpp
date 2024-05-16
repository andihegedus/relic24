﻿#include "TilePiece.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "TileMiniGame.h"
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
		PlayerCharacter->TileGame->OnBecomePossessed();
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("ATilePiece: Ref to Player Character not valid.")); 
	}
}

//TODO: This needs to be edited to only move on the Z and Y axes
void ATilePiece::MoveTile(const FInputActionValue& Value)
{
	FVector Input = Value.Get<FInputActionValue::Axis3D>();

	const FRotator Rotation = Controller->GetControlRotation();
	const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	AddMovementInput(ForwardDirection, Input.Y);

	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	AddMovementInput(RightDirection, Input.X);
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
	
	EnhancedInputComponent->BindAction(PlayerBaseController->MoveAction, ETriggerEvent::Completed, this, &ATilePiece::MoveTile);
	EnhancedInputComponent->BindAction(PlayerBaseController->InteractAction, ETriggerEvent::Completed, this, &ATilePiece::OnBecomeUnPossessed);
	
	ULocalPlayer* LocalPlayer = PlayerBaseController->GetLocalPlayer();

	check(LocalPlayer);
	UEnhancedInputLocalPlayerSubsystem* Subsystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();

	check(Subsystem);
	Subsystem->ClearAllMappings();
	Subsystem->AddMappingContext(PlayerBaseController->PCMappingContext, 0);
}

