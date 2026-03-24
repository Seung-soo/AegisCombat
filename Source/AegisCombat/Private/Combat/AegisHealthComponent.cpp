// Fill out your copyright notice in the Description page of Project Settings.


#include "Combat/AegisHealthComponent.h"

// Sets default values for this component's properties
UAegisHealthComponent::UAegisHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bStartWithTickEnabled = false;
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UAegisHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	MaxHealth = FMath::Max(1.f, MaxHealth);
	Health = FMath::Clamp(Health, 0.f, MaxHealth);

	OnHealthChanged.Broadcast(this, Health, Health, 0.f);
}

void UAegisHealthComponent::ResetToMax()
{
	SetHealth_Internal(MaxHealth);
}

void UAegisHealthComponent::ApplyDamage(float Amount)
{
	if (Amount <= 0.f || IsDead())
		return;

	SetHealth_Internal(Health - Amount);
}

void UAegisHealthComponent::Heal(float Amount)
{
	if (Amount <= 0.f || IsDead())
		return;

	SetHealth_Internal(Health + Amount);
}

float UAegisHealthComponent::GetHealth() const
{
	return (MaxHealth <= 0.f) ? 0.f : (Health / MaxHealth);
}

bool UAegisHealthComponent::IsDead() const
{
	return Health <= 0.f;
}

void UAegisHealthComponent::SetHealth_Internal(float NewHealth)
{
	const float Old = Health;
	Health = FMath::Clamp(NewHealth, 0.f, MaxHealth);

	const float Delta = Health - Old;
	if (!FMath::IsNearlyZero(Delta))
	{
		OnHealthChanged.Broadcast(this, Old, Health, Delta);
	}
}