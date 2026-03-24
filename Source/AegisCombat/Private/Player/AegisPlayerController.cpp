// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/AegisPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "Character/AegisCharacter.h"
#include "Combat/AegisHealthComponent.h"
#include "UI/UAegisHealthHUDWidget.h"

void AAegisPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (HealthWidgetClass)
	{
		HealthWidget = CreateWidget<UUAegisHealthHUDWidget>(this, HealthWidgetClass);
		if (HealthWidget)
		{
			HealthWidget->AddToViewport();
		}
	}

	// 이미 폰이 있으면 바로 바인딩
	BindToPawn(GetPawn());
}

void AAegisPlayerController::SetupInputComponent()
{
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(
		GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
	}
}

void AAegisPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	BindToPawn(InPawn);

	InPawn->OnDestroyed.AddDynamic(this, &AAegisPlayerController::OnPawnDestroyed);
}

void AAegisPlayerController::OnUnPossess()
{
	Unbind();
	Super::OnUnPossess();
}

void AAegisPlayerController::OnPawnDestroyed(AActor* DestroyedActor)
{
	if (AAegisCharacter* RespawnedCharacter = GetWorld()->SpawnActor<AAegisCharacter>(CharacterClass, RespawnTransform))
	{
		Possess(RespawnedCharacter);
	}
}

void AAegisPlayerController::BindToPawn(APawn* BindPawn)
{
	Unbind();
	if (!BindPawn)
		return;

	CachedHealthComp = BindPawn->FindComponentByClass<UAegisHealthComponent>();
	if (!CachedHealthComp)
		return;

	CachedHealthComp->OnHealthChanged.AddDynamic(this, &AAegisPlayerController::HandleHealthChanged);
}

void AAegisPlayerController::Unbind()
{
	if (CachedHealthComp)
	{
		CachedHealthComp->OnHealthChanged.RemoveAll(this);
		CachedHealthComp = nullptr;
	}
}

void AAegisPlayerController::HandleHealthChanged(UAegisHealthComponent* HealthComponent, float OldHealth,
                                                 float NewHealth, float Delta)
{
	if (HealthWidget && HealthComponent)
	{
		HealthWidget->SetHealth(NewHealth, HealthComponent->MaxHealth);
	}
}

void AAegisPlayerController::SetRespawnTransform(const FTransform& NewRespawn)
{
	RespawnTransform = NewRespawn;
}

void AAegisPlayerController::DamageSelf(float Amount)
{
	if (CachedHealthComp)
	{
		CachedHealthComp->ApplyDamage(Amount);
	}
}

void AAegisPlayerController::HealSelf(float Amount)
{
	if (CachedHealthComp)
	{
		CachedHealthComp->Heal(Amount);
	}
}
