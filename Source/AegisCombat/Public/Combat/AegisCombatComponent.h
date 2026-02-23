// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Combat/AegisCombatState.h"
#include "AegisCombatComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class AEGISCOMBAT_API UAegisCombatComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAegisCombatComponent();

public:
	bool TryStartAttack();
	void ForceEndAttack();

protected:
	void SetState(EAegisCombatState NewState);
	
protected:
	UPROPERTY(VisibleAnywhere, Category = "Combat")
	EAegisCombatState State = EAegisCombatState::Idle;
		
};
