#include "Device.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystemInterface.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "Camera/CameraComponent.h"
#include "Engine/InputDelegateBinding.h"
#include "Engine/LocalPlayer.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "relic/PlayerCharacter/PCharacter.h"
#include "relic/PlayerCharacter/PController.h"

ADevice::ADevice()
{
	DeviceMeshComp = CreateDefaultSubobject<UStaticMeshComponent>("InstancedMesh");
	DeviceTimelineComp = CreateDefaultSubobject<UTimelineComponent>(TEXT("DeviceTimelineComp"));
	SetRootComponent(DeviceMeshComp);

	DeviceMovement = CreateDefaultSubobject<UFloatingPawnMovement>("MovementComp");

	// Setup PC Camera components
	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArmComp->SetupAttachment(GetRootComponent());
	
	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComp->SetupAttachment(SpringArmComp, USpringArmComponent::SocketName);

	// Assign SpringArm class variables
	SpringArmComp->TargetArmLength = 300.f;
	//SpringArmComp->bEnableCameraLag = true;
	//SpringArmComp->CameraLagSpeed = 3.0f;

	DeviceTag = "Device";
	DeviceMeshComp->ComponentTags.Add(DeviceTag);
	this->Tags.Add(DeviceTag);
}

void ADevice::BeginPlay()
{
	Super::BeginPlay();

	UpdateFunctionFloatCeiling.BindDynamic(this, &ADevice::UpdateTimelineComp);

	PlayerCharacter = Cast<APCharacter>(GetWorld()->GetGameInstance()->GetFirstLocalPlayerController()->GetPawn());

	/*if (PlayerCharacter)
	{
		PlayerCharacter->OnDeviceActivated.AddUObject(this, &ADevice::OnPuzzleSolved);
		PlayerCharacter->OnDeviceAbandoned.AddUObject(this, &ADevice::OnPuzzleAbandoned);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("TombCeilingDoor: player ref not valid")); 
	}

	if (DeviceTimelineCurveFloat)
	{
		DeviceTimelineComp->AddInterpFloat(DeviceTimelineCurveFloat, UpdateFunctionFloatCeiling);
	}*/
}

void ADevice::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent);
	APController* PlayerBaseController = CastChecked<APController>(Controller);

	EnhancedInputComponent->BindAction(PlayerBaseController->MoveAction, ETriggerEvent::Triggered, this, &ADevice::Move);

	ULocalPlayer* LocalPlayer = PlayerBaseController->GetLocalPlayer();

	check(LocalPlayer);
	UEnhancedInputLocalPlayerSubsystem* Subsystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();

	check(Subsystem);
	Subsystem->ClearAllMappings();
	Subsystem->AddMappingContext(PlayerBaseController->PCMappingContext, 0);
}

void ADevice::Move(const FInputActionValue& Value)
{
	FVector Input = Value.Get<FInputActionValue::Axis3D>();

	const FRotator Rotation = Controller->GetControlRotation();
	const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	AddMovementInput(ForwardDirection, Input.Y);

	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	AddMovementInput(RightDirection, Input.X);
}


/*
void ADevice::PawnClientRestart()
{
	if (PlayerCharacter)
	{
		if (InputComponent == nullptr)
		{
			SetupPlayerInputComponent(InputComponent);
			InputComponent->RegisterComponent();

			if (UInputDelegateBinding::SupportsInputDelegate(GetClass()))
			{
				InputComponent->bBlockInput = bBlockInput;
				UInputDelegateBinding::BindInputDelegatesWithSubojects(this, InputComponent);
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("ADevice: binding input delegate not allowed")); 
			}
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("ADevice: PawnClientRestart refs not valid")); 
	}
}*/

void ADevice::OnBecomePossessed()
{
	if (PlayerCharacter)
	{
		PlayerCharacter->GetController()->Possess(this);
		AutoPossessPlayer = EAutoReceiveInput::Player0;

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

void ADevice::UpdateTimelineComp(float Output)
{
	FRotator CurrentDeviceRotation = this->GetActorRotation();
	
	FRotator NewDeviceRotation = FRotator(Output, CurrentDeviceRotation.Yaw, CurrentDeviceRotation.Roll);
	DeviceMeshComp->SetRelativeRotation(NewDeviceRotation);
}

void ADevice::OnPuzzleSolved()
{
	
	// potentially pawn possession here?
	
	DeviceTimelineComp->Play();

	if (!DeviceTimelineComp->IsPlaying())
	{
		Destroy();
	}
	
}

void ADevice::OnPuzzleAbandoned()
{
	DeviceTimelineComp->Reverse();
}


	


