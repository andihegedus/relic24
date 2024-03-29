﻿#include "PCharacter.h"

#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Engine/LocalPlayer.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "relic/Items/Pickup.h"
#include "relic/System/RelicHUD.h"
#include "relic/PlayerCharacter/PController.h"

APCharacter::APCharacter()
{
	// Setup PC Camera components
	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArmComp->SetupAttachment(GetRootComponent());
	
	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComp->SetupAttachment(SpringArmComp, USpringArmComponent::SocketName);

	// Assign SpringArm class variables
	SpringArmComp->TargetArmLength = 300.f;
	SpringArmComp->bEnableCameraLag = true;
	SpringArmComp->CameraLagSpeed = 3.0f;

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
	MaxInteractTime = 4.f;
}

void APCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (GetWorld()->TimeSince(InteractionInfo.CheckLastInteractionTime) > CheckInteractionFrequency)
	{
		CheckForInteractable();
	}
}

void APCharacter::BeginPlay()
{
	Super::BeginPlay();

	HUD = Cast<ARelicHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
}

void APCharacter::Idle()
{
}

void APCharacter::Move(const FInputActionValue& Value)
{
	FVector Input = Value.Get<FInputActionValue::Axis3D>();

	const FRotator Rotation = Controller->GetControlRotation();
	const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	AddMovementInput(ForwardDirection, Input.Y);

	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	AddMovementInput(RightDirection, Input.X);
}

void APCharacter::Look(const FInputActionValue& Value)
{
	FRotator Input(Value[0], Value[1], Value[2]);
	
	AddControllerYawInput(Input.Yaw);
	
	AddControllerPitchInput(Input.Pitch);
	
	SpringArmComp->SetRelativeRotation(Input);
}

void APCharacter::CheckForInteractable()
{
	//check(GEngine != nullptr);
	
	InteractionInfo.CheckLastInteractionTime = GetWorld()->GetTimeSeconds();
	
	LineTraceStart = GetPawnViewLocation();
	
	FVector LineTraceEnd{LineTraceStart + (GetViewRotation().Vector() * CheckInteractionDistance)};
	float LookDirection = FVector::DotProduct(GetActorForwardVector(), GetViewRotation().Vector());

	if (LookDirection > 0)
	{
		// Visualize our trace hit line
		DrawDebugLine(GetWorld(), LineTraceStart, LineTraceEnd, FColor::Magenta, false, 1.0f, 0, 2.f);

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
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("Pickup not valid."));
			}
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Look direction is 0"));
	}
	
	NoInteractableFound();
	TagInFocus.Empty();
}

void APCharacter::FoundInteractable()
{
	if (TagInFocus.Contains("Pickup"))
	{
		//HUD->UpdateInteractionWidgetComponent("Pickup");
	}
	if (TagInFocus.Contains("Device"))
	{
		//HUD->UpdateInteractionWidgetComponent("Device");
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No item tags detected.")); 
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
		GetWorld()->GetTimerManager().SetTimer(InteractionTimerHandle, this, &APCharacter::CompleteInteract, MaxInteractTime, false);
	}
}

void APCharacter::CompleteInteract()
{
	bIsInteracting = false;

	GetWorldTimerManager().ClearTimer(InteractionTimerHandle);
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

	ULocalPlayer* LocalPlayer = PlayerBaseController->GetLocalPlayer();

	check(LocalPlayer);
	UEnhancedInputLocalPlayerSubsystem* Subsystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();

	check(Subsystem);
	Subsystem->ClearAllMappings();
	Subsystem->AddMappingContext(PlayerBaseController->PCMappingContext, 0);
}