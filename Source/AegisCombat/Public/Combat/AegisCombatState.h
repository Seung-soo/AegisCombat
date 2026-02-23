// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "AegisCombatState.generated.h"

UENUM(BlueprintType)
enum class EAegisCombatState : uint8
{
	Idle UMETA(DisplayName="Idle"),
	Attacking UMETA(DisplayName="Attacking"),
};