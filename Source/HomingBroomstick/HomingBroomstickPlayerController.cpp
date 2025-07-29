// Copyright Epic Games, Inc. All Rights Reserved.


#include "HomingBroomstickPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "Engine/LocalPlayer.h"
#include "InputMappingContext.h"
#include "HomingBroomstickCameraManager.h"

AHomingBroomstickPlayerController::AHomingBroomstickPlayerController()
{
	// set the player camera manager class
	PlayerCameraManagerClass = AHomingBroomstickCameraManager::StaticClass();
}

void AHomingBroomstickPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	// Add Input Mapping Context
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		for (UInputMappingContext* CurrentContext : DefaultMappingContexts)
		{
			Subsystem->AddMappingContext(CurrentContext, 0);
		}
	}
}
