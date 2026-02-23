// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/AegisPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "Core/AegisLog.h"

AAegisPlayerController::AAegisPlayerController()
{
}

void AAegisPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (!IsLocalController())
	{
		return;
	}

	if (!DefaultMappingContext)
	{
		UE_LOG(LogAegis, Warning, TEXT("DefaultMappingContext not set on PlayerController"));
		return;
	}

	ULocalPlayer* LP = GetLocalPlayer();
	if (!LP)
	{
		UE_LOG(LogAegis, Error, TEXT("No LocalPlayer"));
		return;
	}

	UEnhancedInputLocalPlayerSubsystem* Subsystem = LP->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
	if (!Subsystem)
	{
		UE_LOG(LogAegis, Error, TEXT("No EnhancedInputLocalPlayerSubsystem"));
		return;
	}



	Subsystem->AddMappingContext(DefaultMappingContext, 0);
	UE_LOG(LogAegis, Log, TEXT("Added Mapping Context: %s"), *DefaultMappingContext.GetName());
}
