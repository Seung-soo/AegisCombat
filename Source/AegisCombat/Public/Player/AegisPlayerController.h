// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "AegisPlayerController.generated.h"

class UInputMappingContext;

/**
 * 
 */
UCLASS()
class AEGISCOMBAT_API AAegisPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AAegisPlayerController();

protected:
	virtual void BeginPlay() override;

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputMappingContext> DefaultMappingContext;
};
