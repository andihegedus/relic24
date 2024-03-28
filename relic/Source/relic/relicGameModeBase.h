// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "relicGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class RELIC_API ARelicGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

protected:
	// FUNCTIONS
	// -----------------------------
	ARelicGameModeBase(const FObjectInitializer& ObjectInitializer);

	virtual void BeginPlay() override;
};
