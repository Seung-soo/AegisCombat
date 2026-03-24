// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "AegisPlayerController.generated.h"

class AAegisCharacter;
class UInputMappingContext;
class UAegisHealthComponent;
class UUAegisHealthHUDWidget;

/**
 * 
 */
UCLASS()
class AEGISCOMBAT_API AAegisPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
	virtual void OnPossess(APawn* InPawn) override;
	virtual void OnUnPossess() override;

public:
	void SetRespawnTransform(const FTransform& NewRespawn);

	UFUNCTION(Exec)
	void DamageSelf(float Amount = 10.f);

	UFUNCTION(Exec)
	void HealSelf(float Amount = 10.f);

protected:
	UFUNCTION()
	void OnPawnDestroyed(AActor* DestroyedActor);

private:
	void BindToPawn(APawn* Pawn);
	void Unbind();

	UFUNCTION()
	void HandleHealthChanged(UAegisHealthComponent* HealthComponent, float OldHealth, float NewHealth, float Delta);

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputMappingContext> DefaultMappingContext;

	UPROPERTY(EditAnywhere, Category = "Respawn")
	TSubclassOf<AAegisCharacter> CharacterClass;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UUAegisHealthHUDWidget> HealthWidgetClass;

	FTransform RespawnTransform;

private:
	UPROPERTY()
	TObjectPtr<UUAegisHealthHUDWidget> HealthWidget;

	UPROPERTY()
	TObjectPtr<UAegisHealthComponent> CachedHealthComp;
};
