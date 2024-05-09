#include "Device.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystemInterface.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "Camera/CameraComponent.h"
#include "Engine/LocalPlayer.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "relic/PlayerCharacter/PCharacter.h"
#include "relic/PlayerCharacter/PController.h"
#include "relic/System/RelicHUD.h"

ADevice::ADevice()
{
	DeviceMeshComp = CreateDefaultSubobject<UStaticMeshComponent>("InstancedMesh");
	DeviceTimelineComp = CreateDefaultSubobject<UTimelineComponent>(TEXT("DeviceTimelineComp"));
	SetRootComponent(DeviceMeshComp);

	DeviceMovement = CreateDefaultSubobject<UFloatingPawnMovement>("MovementComp");

	// Setup PC Camera components
	//SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	//SpringArmComp->SetupAttachment(GetRootComponent());
	
	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComp->SetupAttachment(DeviceMeshComp);

	// might not need this
	//OriginalRotation = GetActorRotation();
	
	// Assign SpringArm class variables
	//SpringArmComp->TargetArmLength = 300.f;
	//SpringArmComp->SetAbsolute(true, true);
	//
	
	DeviceTag = "Device";
	DeviceMeshComp->ComponentTags.Add(DeviceTag);
	this->Tags.Add(DeviceTag);
}

void ADevice::BeginPlay()
{
	Super::BeginPlay();

	UpdateFunctionFloat.BindDynamic(this, &ADevice::UpdateTimelineComp);

	if (DeviceTimelineCurveFloat)
	{
		DeviceTimelineComp->AddInterpFloat(DeviceTimelineCurveFloat, UpdateFunctionFloat);
	}

	PlayerCharacter = Cast<APCharacter>(GetWorld()->GetGameInstance()->GetFirstLocalPlayerController()->GetPawn());

	HUD = Cast<ARelicHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());

	OnTimelineEnd.BindDynamic(this, &ADevice::OnPuzzleSolved);

	DeviceTimelineComp->SetTimelinePostUpdateFunc(OnTimelineEnd);
}

void ADevice::Move(const FInputActionValue& Value)
{
	DeviceTimelineComp->Play();
}

void ADevice::StopMove(const FInputActionValue& Value)
{
	DeviceTimelineComp->Reverse();
}

void ADevice::OnPuzzleSolved()
{
	if (DeviceMeshComp->GetComponentRotation() == FRotator(90.f,180.f,180.f))
	{
		UE_LOG(LogTemp, Warning, TEXT("ADevice: Puzzle solved!"));

		DeviceTimelineComp->Stop();

		OnBecomeUnPossessed();

		//TODO: Figure out how to make object shatter, play that animation here before destruction

		this->Destroy();
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("ADevice: Puzzle in progress..."));

		//FRotator Rotation = DeviceMeshComp->GetComponentRotation();

		//UE_LOG(LogTemp, Warning, TEXT("%s"), *Rotation.ToString());
	}
}

void ADevice::OnPuzzleAbandoned()
{
	DeviceTimelineComp->Reverse();
	
	OnBecomeUnPossessed();
}

void ADevice::OnBecomePossessed()
{
	DeviceTimelineComp->Stop();
	
	if (PlayerCharacter)
	{
		PlayerCharacter->GetController()->Possess(this);
		AutoPossessPlayer = EAutoReceiveInput::Player0;
		PlayerCharacter->SetActorHiddenInGame(true);

		HUD->HideInteractionWidget();

		FString CheckController = this->GetController()->GetName();
		UE_LOG(LogTemp, Warning, TEXT(" %s "), *CheckController);

		PlayerController = Cast<APController>(this->Controller);
		
		if (PlayerController)
		{
			PCMappingContext = {PlayerController->PCMappingContext};
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("ADevice: Ref to Player Contoller not valid."));

		}
		
		
		UE_LOG(LogTemp, Warning, TEXT("ADevice: All refs valid. Pawn should be possessed."));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("ADevice: Ref to Player Character not valid.")); 

	}
	
}

void ADevice::OnBecomeUnPossessed()
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
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("ADevice: Ref to Player Contoller not valid."));

		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("ADevice: Ref to Player Character not valid.")); 

	}
}

void ADevice::UpdateTimelineComp(float Output)
{
	FRotator CurrentDeviceRotation = this->GetActorRotation();
	FVector CurrentCameraLocation =  CameraComp->GetComponentLocation();
	
	CameraComp->SetWorldRotation(FRotator(0,90.f,0));
	CameraComp->SetWorldLocation(CurrentCameraLocation);
	CameraComp->SetAbsolute(false, false);
	
	FRotator NewDeviceRotation = FRotator(Output, CurrentDeviceRotation.Yaw, CurrentDeviceRotation.Roll);
	DeviceMeshComp->SetRelativeRotation(NewDeviceRotation);
}



void ADevice::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent);
	APController* PlayerBaseController = CastChecked<APController>(Controller);
	
	EnhancedInputComponent->BindAction(PlayerBaseController->DeviceAction, ETriggerEvent::Triggered, this, &ADevice::Move);
	EnhancedInputComponent->BindAction(PlayerBaseController->DeviceAction, ETriggerEvent::Completed, this, &ADevice::StopMove);
	EnhancedInputComponent->BindAction(PlayerBaseController->EscapeAction, ETriggerEvent::Completed, this, &ADevice::OnPuzzleAbandoned);

	ULocalPlayer* LocalPlayer = PlayerBaseController->GetLocalPlayer();

	check(LocalPlayer);
	UEnhancedInputLocalPlayerSubsystem* Subsystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();

	check(Subsystem);
	Subsystem->ClearAllMappings();
	Subsystem->AddMappingContext(PlayerBaseController->PCMappingContext, 0);
}


	


