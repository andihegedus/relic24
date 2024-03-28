// Copyright Epic Games, Inc. All Rights Reserved.


#include "relicGameModeBase.h"

#include "System/RelicHUD.h"

ARelicGameModeBase::ARelicGameModeBase(const FObjectInitializer& ObjectInitializer)
{
	HUDClass = ARelicHUD::StaticClass();
}

void ARelicGameModeBase::BeginPlay()
{
	Super::BeginPlay();
}

