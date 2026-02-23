// Fill out your copyright notice in the Description page of Project Settings.


#include "Combat/AegisCombatComponent.h"

#include "Core/AegisLog.h"

// Sets default values for this component's properties
UAegisCombatComponent::UAegisCombatComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bStartWithTickEnabled = false;
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

bool UAegisCombatComponent::TryStartAttack()
{
	if (State != EAegisCombatState::Idle)
	{
		UE_LOG(LogAegisCombat, Log, TEXT("TryStartAttack blocked. State = %d"), (int32)State);
		return false;
	}

	SetState(EAegisCombatState::Attacking);
	return true;
}

void UAegisCombatComponent::ForceEndAttack()
{
	if (State == EAegisCombatState::Attacking)
	{
		SetState(EAegisCombatState::Idle);
	}
}

void UAegisCombatComponent::SetState(EAegisCombatState NewState)
{
	if (State == NewState)
		return;

	UE_LOG(LogAegisCombat, Log, TEXT("CombatState: %d -> %d"), (int32)State, (int32)NewState);
	State = NewState;
}