// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UAegisHealthHUDWidget.generated.h"

class UTextBlock;
class UProgressBar;
/**
 * 
 */
UCLASS()
class AEGISCOMBAT_API UUAegisHealthHUDWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Health HUD")
	void SetHealth(float Current, float Max);

protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UProgressBar> PB_Health;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> TXT_Health;
};
