#include "PCharacter.h"

APCharacter::APCharacter()
{
}

void APCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void APCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void APCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}
