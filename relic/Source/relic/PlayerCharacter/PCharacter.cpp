﻿#include "PCharacter.h"

#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Components/SphereComponent.h"
#include "Engine/LocalPlayer.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/KismetStringLibrary.h"
#include "relic/Items/DialogueTrigger.h"
#include "relic/Items/PuzzleItems/Device.h"
#include "relic/Items/PuzzleItems/TileMiniGame.h"
#include "relic/System/RelicHUD.h"
#include "relic/PlayerCharacter/PController.h"
#include "relic/UserInterface/PlayerState/OxygenMeterWidget.h"

APCharacter::APCharacter()
{
	// Setup PC Camera components
	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArmComp->SetupAttachment(GetRootComponent());
	
	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComp->SetupAttachment(SpringArmComp, USpringArmComponent::SocketName);

	PlayerHead = CreateDefaultSubobject<USphereComponent>(TEXT("Head"));
	PlayerHead->AttachToComponent(this->GetMesh(), FAttachmentTransformRules::KeepRelativeTransform);

	// Assign SpringArm class variables
	SpringArmComp->TargetArmLength = 0.f;
	SpringArmComp->bEnableCameraLag = false;
	//SpringArmComp->CameraLagSpeed = 3.0f;
	SpringArmComp->bUsePawnControlRotation = true;

	// Take control of the default player
	AutoPossessPlayer = EAutoReceiveInput::Player0;

	// Untick inherit R,P,Y for character
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	// Rotate character towards direction of acceleration 
	GetCharacterMovement()->bOrientRotationToMovement = true;

	// Interaction variables
	LineTraceStart = {FVector::ZeroVector};
	CheckInteractionDistance = 200.f;
	CheckInteractionFrequency = 0.025;
	MaxInteractTime = 120.f;

	// Timer to start after puzzles are solved
	DelayAfterSolution = 60.f;

	DiveTimerLoopCount = 0;
	DeviceTimerLoopCount = 0;

	WaterLevelID = 1;
	
	// Might not be necessary
	PlayerTag = "Player";
	this->Tags.Add(PlayerTag);
}

void APCharacter::BeginPlay()
{
	Super::BeginPlay();

	HUD = Cast<ARelicHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
	
	// Inventory variables
	InventoryQuantity = 0;
	bIsDiving = false;
}

void APCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (GetWorld()->TimeSince(InteractionInfo.CheckLastInteractionTime) > CheckInteractionFrequency)
	{
		CheckForInteractable();
	}

	if (this->GetCharacterMovement()->IsInWater() && !BodiesOfWater.IsEmpty())
	{
		FString Diving = UKismetStringLibrary::Conv_BoolToString(PlayerHead->IsOverlappingActor(BodiesOfWater[0]));
		//UE_LOG(LogTemp, Warning, TEXT("%s"), *Diving);
		
		if (PlayerHead->IsOverlappingActor(BodiesOfWater[0]))
		{
			bIsDiving = true;
			DiveTimer();
		}
		else
		{
			bIsDiving = false;
			DiveTimer();
			BodiesOfWater.Empty();
		}
	}
	else
	{
		bIsDiving = false;
		DiveTimer();
		//UE_LOG(LogTemp, Warning, TEXT("bisDiving is false."));
	}

	HUD->OxygenMeterWidget->UpdateWidget(OxygenTimerHandle, 100.f - DiveTimerLoopCount);

	HUD->OxygenMeterWidget->SetRoundPBPercent((100.f - DiveTimerLoopCount) / 100.f);

	//FString Diving = UKismetStringLibrary::Conv_BoolToString(BodiesOfWater.IsEmpty());
	//UE_LOG(LogTemp, Warning, TEXT("%s"), *Diving);
}

void APCharacter::Idle()
{
}

void APCharacter::Move(const FInputActionValue& Value)
{
	//FString Diving = UKismetStringLibrary::Conv_BoolToString(bIsDiving);
	//UE_LOG(LogTemp, Warning, TEXT("%s"), *Diving);
	
	if (this->GetCharacterMovement()->IsSwimming())
	{
		FVector Input = Value.Get<FInputActionValue::Axis3D>();
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(Rotation.Pitch, Rotation.Yaw, 0.f);
		
		PlayerHead->SetRelativeRotation(Controller->GetControlRotation()); 

		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(ForwardDirection, Input.Y);

		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(RightDirection, Input.X);
	}
	else
	{
		FVector Input = Value.Get<FInputActionValue::Axis3D>();

		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(ForwardDirection, Input.Y);

		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(RightDirection, Input.X);
	}
	
}

void APCharacter::Look(const FInputActionValue& Value)
{
	FRotator Input(Value[0], Value[1], Value[2]);
	
	AddControllerYawInput(Input.Yaw);
	
	AddControllerPitchInput(Input.Pitch);
	
	SpringArmComp->SetRelativeRotation(Input);
}

void APCharacter::DiveTimer()
{
	if (bIsDiving)
	{
		GetWorld()->GetTimerManager().SetTimer(OxygenTimerHandle, this, &APCharacter::DiveTimer, 1.f, true);

		if (DiveTimerLoopCount < 100.f)
		{
			DiveTimerLoopCount += 0.025f;
		}
		
		if (DiveTimerLoopCount >= 100.f)
		{
			Death();
			HUD->OxygenMeterWidget->UpdateWidget(OxygenTimerHandle, 0.f);
			GetWorld()->GetTimerManager().ClearTimer(OxygenTimerHandle);
			// End state
		}
	}
	else if (!bIsDiving)
	{
		if (DiveTimerLoopCount > 0.f)
		{
			DiveTimerLoopCount -= 0.25;

			if (DiveTimerLoopCount == 0.f)
			{
				GetWorld()->GetTimerManager().ClearTimer(OxygenTimerHandle);
			}
		}
	}
	
}

void APCharacter::CheckForInteractable()
{
	InteractionInfo.CheckLastInteractionTime = GetWorld()->GetTimeSeconds();
	
	LineTraceStart = GetPawnViewLocation();
	
	FVector LineTraceEnd{LineTraceStart + (GetViewRotation().Vector() * CheckInteractionDistance)};
	float LookDirection = FVector::DotProduct(GetActorForwardVector(), GetViewRotation().Vector());

	if (LookDirection > 0)
	{
		// Visualize our trace hit line
		//DrawDebugLine(GetWorld(), LineTraceStart, LineTraceEnd, FColor::Magenta, false, 1.0f, 0, 2.f);

		// Contains useful things for line tracing
		FCollisionQueryParams QueryParams;

		// I'm the class shooting out the line trace, don't want to hit myself
		QueryParams.AddIgnoredActor(this);

		// Store the result of the line trace, also contains the actor that was hit
		FHitResult TraceHit;

		// Get our hit result by reference, this function will modify it, it becomes the output
		if(GetWorld()->LineTraceSingleByChannel(TraceHit, LineTraceStart, LineTraceEnd, ECC_Visibility, QueryParams))
		{
			if (TraceHit.GetActor()->Tags.Contains("Pickup"))
			{
				CurrentTag = "Pickup";
				TagInFocus.Add(CurrentTag);
		
				FoundInteractable();

				ItemsToDestroy.Add(TraceHit.GetActor());
				
				return;
			}
			if (TraceHit.GetActor()->Tags.Contains("Device")) 
			{
				CurrentTag = "Device";
				TagInFocus.Add(CurrentTag);
		
				FoundInteractable();
				
				ItemsToDestroy.Add(TraceHit.GetActor());

				return;
			}
			if (TraceHit.GetActor()->Tags.Contains("Slot")) 
			{
				CurrentTag = "Slot";
				TagInFocus.Add(CurrentTag);
		
				FoundInteractable();

				ItemsToAppear.Add(TraceHit.GetActor());

				return;
			}
			if (TraceHit.GetActor()->Tags.Contains("TileGame")) 
			{
				CurrentTag = "TileGame";
				TagInFocus.Add(CurrentTag);
		
				FoundInteractable();

				PuzzlesToSolve.Add(TraceHit.GetActor());

				return;
			}
			if (TraceHit.GetActor()->Tags.Contains("TombWater")) 
			{
				CurrentTag = "TombWater";
				WaterInVision.Add(CurrentTag);
		
				FoundInteractable();

				BodiesOfWater.Add(TraceHit.GetActor());

				return;
			}
		}
	}
	
	NoInteractableFound();
	TagInFocus.Empty();

	// TODO: These could potentially be narrowed down to one array, since player should only be able to interact with one item at a time
	ItemsToDestroy.Empty();
	ItemsToAppear.Empty();
	PuzzlesToSolve.Empty();
}

void APCharacter::FoundInteractable()
{
	if (TagInFocus.Contains("Pickup"))
	{
		HUD->UpdateInteractionWidget("Pickup");
	}
	if (TagInFocus.Contains("Device"))
	{
		HUD->UpdateInteractionWidget("Device");
	}
	if (TagInFocus.Contains("Slot"))
	{
		HUD->UpdateInteractionWidget("Slot");
	}
	if (TagInFocus.Contains("TileGame"))
	{
		HUD->UpdateInteractionWidget("TileGame");
	}
}

void APCharacter::NoInteractableFound()
{
	HUD->HideInteractionWidget();
}

void APCharacter::StartInteract()
{
	CheckForInteractable();
	
	bIsInteracting = true;

	if (TagInFocus.Contains("Device"))
	{
		DeviceRef = Cast<APawn>(ItemsToDestroy[0]);

		if (DeviceRef)
		{
			Device = Cast<ADevice>(DeviceRef);

			if (Device)
			{
				Device->OnBecomePossessed();
				HUD->HideInteractionWidget();
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("APCharacter: Reference to Device pawn is not valid."));
			}
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("APCharacter: DeviceRef cast to pawn failed."));
		}
	}
	if (TagInFocus.Contains("TileGame"))
	{
		TileGameRef = Cast<APawn>(PuzzlesToSolve[0]);

		if (TileGameRef)
		{
			TileGame = Cast<ATileMiniGame>(TileGameRef);

			if (TileGame)
			{
				TileGame->OnBecomePossessed();
				HUD->HideInteractionWidget();
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("APCharacter: Reference to TileMiniGame pawn is not valid.")); 
			}
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("APCharacter: TileGameRef cast to pawn failed."));
		}
	}
	if (TagInFocus.Contains("Slot"))
	{
		
	}
}

void APCharacter::DeviceAbandoned()
{
	bIsInteracting = false;
	
}

void APCharacter::TilePuzzleSolved()
{
	WaterLevelID = 2;
	OnTilePuzzleSolved.Broadcast();
	OnCheckpointReached.Broadcast();
}

void APCharacter::CompleteInteract()
{
	bIsInteracting = false;
	
	if (TagInFocus.Contains("Pickup"))
	{
		HUD->UpdateInventoryWidget("Pickup");

		InventoryQuantity++;

		ItemsToDestroy[0]->Destroy();
	}
	if (TagInFocus.Contains("Slot"))
	{
		ItemsToAppear[0]->Tags.Empty();
		
		if (InventoryQuantity >= 1)
		{
			ItemsToAppear[0]->SetActorHiddenInGame(false);
			
			InventoryQuantity--;
		}

		if (MedallionsPlacedCount < 3)
		{
			MedallionsPlacedCount++;

			if (MedallionsPlacedCount == 1)
			{
				WaterLevelID = 3;
				OnMedallionPlaced.Broadcast();
				OnCheckpointReached.Broadcast();
			}
		}
		else
		{
			if (MedallionsPlacedCount == 3)
			{
				OnMedallionPlaced.Broadcast();
				OnCheckpointReached.Broadcast();
			}
		}
		
		
		HUD->UpdateInventoryWidget("Slot");
	}
	if (TagInFocus.Contains("Device"))
	{
		// Not sure if unpossession will happen here or in the Device script
	}
	if (TagInFocus.Contains("TileGame"))
	{
		// Not sure if unpossession will happen here or in the TileMiniGame script
	}
}

void APCharacter::CloseDialogueBox()
{
	if (TriggerTags.Num() > 0)
	{
		OnEnterButtonPressed.Broadcast();
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("APCharacter: TriggerTags has no elements in it."));
	}

	TriggerTags.Empty();
}


void APCharacter::Death()
{
	check(GEngine != nullptr);
	
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("MORTIS"));

	bIsDiving = false;
}

void APCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent);
	APController* PlayerBaseController = CastChecked<APController>(Controller);

	check(EnhancedInputComponent && PlayerBaseController);

	EnhancedInputComponent->BindAction(PlayerBaseController->MoveAction, ETriggerEvent::Triggered, this, &APCharacter::Move);
	EnhancedInputComponent->BindAction(PlayerBaseController->MoveAction, ETriggerEvent::Completed, this, &APCharacter::Idle);
	
	EnhancedInputComponent->BindAction(PlayerBaseController->LookAction, ETriggerEvent::Triggered, this, &APCharacter::Look);
	
	EnhancedInputComponent->BindAction(PlayerBaseController->InteractAction, ETriggerEvent::Triggered, this, &APCharacter::StartInteract);
	EnhancedInputComponent->BindAction(PlayerBaseController->InteractAction, ETriggerEvent::Completed, this, &APCharacter::CompleteInteract);
	
	EnhancedInputComponent->BindAction(PlayerBaseController->CloseDialogueAction, ETriggerEvent::Completed, this, &APCharacter::CloseDialogueBox);

	ULocalPlayer* LocalPlayer = PlayerBaseController->GetLocalPlayer();

	check(LocalPlayer);
	UEnhancedInputLocalPlayerSubsystem* Subsystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();

	check(Subsystem);
	Subsystem->ClearAllMappings();
	Subsystem->AddMappingContext(PlayerBaseController->PCMappingContext, 0);
}
